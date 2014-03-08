# -- coding: utf-8 --
import os
import shutil
import MayaWebSocket
reload(MayaWebSocket)
import maya.cmds as cmds
import maya.mel as mel
from maya import OpenMaya
from maya import OpenMayaUI
import math
import time
from subprocess import Popen


hko_files = [
    "common_scene_no_physics_cm.hko",
    "monk_rig.hko",
    "monk_skin_64_bone.hko",
    "monk_skin_full_bone.hko",
    "monk_aniamtion_no_rootmotion.hko",
    "monk_aniamtion_rootmotion_without_rotation.hko",
    "monk_aniamtion_rootmotion_with_rotation.hko",
    "monk_aniamtion_rootmotion_with_rotation_turn.hko",
    "monk_aniamtion_rootmotion_with_rotation_directional.hko",
    "monk_animation_additive_firstframe.hko"
]


hko_names = [
    "simple scene unit cm",
    "hero rig",
    "hero skin 64 bone limit",
    "hero skin no bone limit",
    "hero animation no rootmotion",
    "hero animation rootmotion no rotation",
    "hero animation rootmotion has rotation",
    "hero animation rootmotion has rotation turn",
    "hero animation rootmotion has rotation directional",
    "hero hero animation rootmotion additive First Frame"
]

button_names = [
    'export',
    'export select only',
    'export and preview',
    'export select only and preview',
    'lunch previwer (automatic remote connect)',
    'lunch test game',
    'lunch game editor',
    'lunch animation editor',
    'remote camera',
    'remote connect',
    'remote disconnect',
]


def nameToNode(name):
    selectionList = OpenMaya.MSelectionList()
    selectionList.add(name)
    node = OpenMaya.MObject()
    selectionList.getDependNode(0, node)
    return node


def uiDeleteCallback(pipe):
    print("ui delete callback")
    pipe.__del__()


def cameraChangedCallback(*args):
    msg = args[0]
    #mplug = args[1]
    #otherMPlug = args[2]
    pipe = args[3]
    if not pipe.isCameraSyncChecked():
        return
    if not (msg & OpenMaya.MNodeMessage.kAttributeSet):
        return
    pipe.syncCamera()


def getCameraFov(cameraName):
    focalStr = cameraName + '.focalLength'
    horStr = cameraName + '.horizontalFilmAperture'
    focal = cmds.getAttr(focalStr)
    print(focal)
    aperture = cmds.getAttr(horStr)
    print(aperture)
    fov = (0.5 * aperture) / (focal * 0.03937)
    fov = 2.0 * math.atan(fov)
    fov = 57.29578 * fov
    fov = fov / 1.33333333
    return fov


def getSceneName():
    fileName = cmds.file(q=True, sn=True)
    print("current scene = " + fileName)
    fileName = os.path.basename(fileName)
    if(not fileName):
        return "test"
    (prefix, sep, suffix) = fileName.rpartition('.')
    return prefix


def getSceneDirectory():
    fileName = cmds.file(q=True, sn=True)
    print("current scene = " + fileName)
    return os.path.dirname(fileName)


class NagaPipeline(object):

    """docstring for ClassName"""

    def __init__(self):
        print("NagaPipeline::__init__")
        self.__createUI()
        self.webSock = MayaWebSocket.MayaWebSocket()
        self.lastSyncTime = time.time()

        self.uiCallback = OpenMayaUI.MUiMessage.addUiDeletedCallback(
            self.myWindow, uiDeleteCallback, self)
        self.cameraCallback = OpenMaya.MNodeMessage.addAttributeChangedCallback(
            nameToNode('persp'), cameraChangedCallback, self)

        fov = getCameraFov('persp')
        print(fov)

        nagaDir = os.environ['NAGA_DIR']
        nagaDir = nagaDir.replace("\\", "/")
        self.pipelinePath = nagaDir + 'Pipeline/'
        self.havokPakPath = 'Data/havok_packages/'
        self.havokExportPath = nagaDir + self.havokPakPath
        self.lastOutputName = ''
        self.havokNodePath = 'Data/havok_packages/'
        self.scale = 0.01

    def __del__(self):
        print("NagaPipeline::__del__")
        self.webSock.disconnect()
        OpenMaya.MMessage.removeCallback(self.uiCallback)
        OpenMaya.MMessage.removeCallback(self.cameraCallback)

    #
    #
    #           GUI      FUNCTIONS
    #
    #
    def __createUI(self):
        self.myUI = 'Naga_UI'
        if cmds.window(self.myUI, exists=True):
            cmds.deleteUI(self.myUI)

        self.myWindow = cmds.window(self.myUI,
                                    t='Naga Pipeline')
        cmds.columnLayout('CL')
        cmds.text(label='havok pipline export type:')
        #===============================================================
        #========== add my hko list to UI ==============================
        self.optionMenu = cmds.optionMenuGrp('Naga_UI_Option',
                                             label='export type',
                                             extraLabel='hko')
        for hko_name in hko_names:
            cmds.menuItem(label=hko_name, p='Naga_UI_Option|OptionMenu')
        #===============================================================

        cmds.text(label='output file name:')
        defaultOutputName = getSceneName() + ".hkx"
        self.outTextField = cmds.textField(
            'Naga_UI_Text', text=defaultOutputName)

        button_commands = [
            self.onExportHKX,
            self.onExportHKXSelectOnly,
            self.onExportHKXAndPreview,
            self.onExportHKXSelectOnlyAndPreview,
            self.onLunchPreviewer,
            self.onLunchTestGame,
            self.onLunchEngineEditor,
            self.onLunchAnimationFSM,
            self.onRemoteCamera,
            self.onRemoteConnect,
            self.onRemoteDisconnect
        ]

        array_len = len(button_names)
        for i in range(array_len):
            cmds.button(label=button_names[i], command=button_commands[i])

        self.cameraCheck = cmds.checkBox(
            label='Camrea Sync', changeCommand=self.checkChanged)

        cmds.showWindow(self.myUI)

    def lunchBat(self, batName, batFolder, wait=False):
        print("bat lunch name %s, folder %s, " % (batName, batFolder))
        p = Popen(batFolder + batName, cwd=batFolder)
        if(wait):
            stdout, stderr = p.communicate()
            print(stdout)
            print(stderr)

    def onExportHKX(self, *arg):
        self.havokExport(False)

    def onExportHKXSelectOnly(self, *arg):
        self.havokExport(True)

    def onExportHKXAndPreview(self, *arg):
        self.havokExport(False)
        self.previewHavok()

    def onExportHKXSelectOnlyAndPreview(self, *arg):
        self.havokExport(True)
        self.previewHavok()

    def onLunchEngineEditor(self, *arg):
        self.lunchBat("naga_editor.bat", os.environ['NAGA_DIR'])

    def onLunchTestGame(self, *arg):
        self.lunchBat("naga_animation.bat", os.environ['NAGA_DIR'])

    def onLunchPreviewer(self, *arg):
        self.lunchBat("hkxSceneViewer.bat", os.environ['NAGA_DIR'])
        self.webSock.connect(self.onWebSocketOpen)

    def onLunchAnimationFSM(self, *arg):
        self.lunchBat("naga_animation_fsm.as", os.environ['NAGA_DIR'])

    def onRemoteCamera(self, *arg):
        self.syncCamera()

    def onRemoteConnect(self, *arg):
        self.webSock.connect(self.onWebSocketOpen)

    def onRemoteDisconnect(self, *arg):
        self.webSock.disconnect()

    def checkChanged(self, *arg):
        pass

    def isCameraSyncChecked(self):
        return cmds.checkBox(self.cameraCheck, query=True, value=True)

    def previewHavok(self):
        if(self.webSock.closed):
            filePath = os.environ['NAGA_DIR']
            fileName = filePath + 'hkxSceneViewer.bat'
            hkxFile = self.havokNodePath + self.lastOutputName
            args = [fileName, '-havokfile', hkxFile]
            Popen(args, cwd=filePath)
            time.sleep(1)
            self.webSock.connect(self.onWebSocketOpen)
    #
    #
    #           EXPORT      FUNCTIONS
    #
    #

    def havokExport(self, selectOnly):
        selectedType = cmds.optionMenuGrp(self.optionMenu,
                                          query=True,
                                          select=True)
        selectedType -= 1
        output_name = cmds.textField(self.outTextField, query=True, text=True)
        if (output_name != '' and selectedType >= 0):
            self.exportToHKX(in_type=selectedType,
                             in_filename=output_name,
                             rigFile='monk_rig.txt',
                             select_only=selectOnly)
        else:
            raise "output file is empty or export type is null!"

    def exportToHKX(self, in_type, in_filename, rigFile='', envArgs='', select_only=False):
        hko_filename = hko_files[in_type]
        hko_fullpath = self.pipelinePath + hko_filename
        print("hko file = " + hko_fullpath)
        file_name = self.havokExportPath + in_filename
        print("out file = " + file_name)
        self.lastOutputName = in_filename

        # -v means visible only.
        eval_cmd = "hkCmdExportScene -o \"" + hko_fullpath + "\" -b -v "
        if select_only:
            eval_cmd += "-s "
        eval_cmd += "-ev "
        envCmd = "HK_OUTPUT=" + file_name + ";"
        # set workspace to enviroment
        workSpace = cmds.workspace(q=True, dir=True)
        envCmd += "WORK_SPACE=" + workSpace + ";"
        if(envArgs):
            envCmd += envArgs
        eval_cmd += '"' + envCmd + '"'
        print(eval_cmd)

        sceneDir = getSceneDirectory()
        print("scene dir = " + sceneDir)
        tmpRigFile = sceneDir + "\\output_rig.txt"

        if(rigFile):
            shutil.copyfile(self.pipelinePath + rigFile, tmpRigFile)

        mel.eval(eval_cmd)
    #
    #
    #         ENGINE SYNC   FUNCTIONS
    #
    #

    def onWebSocketOpen(self):
        print("\n\nonWebSocketOpen\n\n")
        # self.syncCamera()

    def syncCamera(self):
        curTime = time.time()
        dt = curTime - self.lastSyncTime
        if(dt < 0.01):
            return

        self.lastSyncTime = curTime

        tx = cmds.getAttr("persp.tx") * self.scale
        ty = cmds.getAttr("persp.ty") * self.scale
        tz = cmds.getAttr("persp.tz") * self.scale
        rx = cmds.getAttr("persp.rx")
        ry = cmds.getAttr("persp.ry")
        rz = cmds.getAttr("persp.rz")

        senddata = '%f,%f,%f,%f,%f,%f' % (tx, ty, tz, rx, ry, rz)

        # print(senddata)
        self.webSock.sendmayacommand("camera_transform", senddata)
