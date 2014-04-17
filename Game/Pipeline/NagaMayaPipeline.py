# -- coding: utf-8 --
import os
import shutil
import MayaWebSocket
reload(MayaWebSocket)
import maya.cmds as cmds
import maya.mel as mel
import maya.OpenMaya as OM
import maya.OpenMayaUI as OMUI
import math
import time
from subprocess import Popen

#
# the default unit in maya is centimeter
# so every model we scale down 0.01 to engine.
#
HKO_FILES = [
    "common_scene_no_physics_cm.hko",
    "character_skin_full_bone.hko",
    "character_aniamtion_no_rootmotion.hko",
    "character_aniamtion_rootmotion_without_rotation.hko",
    "character_aniamtion_rootmotion_with_rotation.hko",
    "character_animation_additive_firstframe.hko",
]

HKO_NAMES = [
    "simple scene no physics",
    "skin",
    "animation default",
    "animation RM",
    "animation RM --rot",
    "animation ADDITIVE"
]


def nameToNode(name):
    selectionList = OM.MSelectionList()
    selectionList.add(name)
    node = OM.MObject()
    selectionList.getDependNode(0, node)
    return node


def uiDeleteCallback(pipe):
    print("ui delete callback")
    pipe.__del__()


def osGetFileList(directory, ext):
    fileList = []
    for root, dirs, files in os.walk(directory):
        for name in files:
            #path = os.path.join(root, name)
            if name.endswith(ext):
                fileList.append(name)
    return fileList


def clearMenu(menuName):
    # itemListLong returns the children
    menuItems = cmds.optionMenu(menuName, q=True, itemListLong=True)
    if menuItems:
        cmds.deleteUI(menuItems)


def attrChangedCallback(msg, mplug, otherMplug, pipe):
    if not pipe.isSyncChecked():
        return
    if not (msg & OM.MNodeMessage.kAttributeSet):
        return
    nodeName, attrName = mplug.name().split('.')
    pipe.remoteSyncTransform(str(nodeName))


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


def exportKeys(boneNames, exportFileName):
    myFileObject = open(exportFileName, 'w')
    theData = []
    minTime = cmds.playbackOptions(q=1, min=1)
    maxTime = cmds.playbackOptions(q=1, max=1)
    minTime = int(minTime)
    maxTime = int(maxTime)
    for frame in range(minTime, maxTime + 1):
        cmds.currentTime(frame)
        for boneName in boneNames:
            translateX = cmds.getAttr(boneName + '.translateX')
            translateY = cmds.getAttr(boneName + '.translateY')
            translateZ = cmds.getAttr(boneName + '.translateZ')
            rotateX = cmds.getAttr(boneName + '.rotateX')
            rotateY = cmds.getAttr(boneName + '.rotateY')
            rotateZ = cmds.getAttr(boneName + '.rotateZ')
            theLine = '%s,%g,%g,%g,%g,%g,%g,%g\n' % (boneName,
                                                     frame,
                                                     translateX,
                                                     translateY,
                                                     translateZ,
                                                     rotateX,
                                                     rotateY,
                                                     rotateZ)
            theData.append(theLine)
    for lines in theData:
        myFileObject.writelines(lines)
    myFileObject.close()


def importKeys(keyFileName, scale=1.0):
    myFileObject = open(keyFileName, 'r')
    theLines = myFileObject.readlines()
    #minTime = 9999
    #maxTime = -1

    # cut all keys first.
    for line in theLines:
        theSplit = line.split(',')
        cmds.cutKey(theSplit[0])

    # set all keys to joint!
    for line in theLines:
        theSplit = line.split(',')
        theName = theSplit[0]
        theFrame = int(theSplit[1])
        translateX = float(theSplit[2]) * scale
        translateY = float(theSplit[3]) * scale
        translateZ = float(theSplit[4]) * scale
        rotateX = float(theSplit[5])
        rotateY = float(theSplit[6])
        rotateZ = float(theSplit[7])

        # if(theFrame < minTime):
        #    minTime = theFrame
        # if(theFrame > maxTime):
        #    maxTime = theFrame

        cmds.setKeyframe(
            theName, v=translateX, at='translateX', t=theFrame)
        cmds.setKeyframe(
            theName, v=translateY, at='translateY', t=theFrame)
        cmds.setKeyframe(
            theName, v=translateZ, at='translateZ', t=theFrame)
        cmds.setKeyframe(theName, v=rotateX, at='rotateX', t=theFrame)
        cmds.setKeyframe(theName, v=rotateY, at='rotateY', t=theFrame)
        cmds.setKeyframe(theName, v=rotateZ, at='rotateZ', t=theFrame)
        print('set key ', theFrame)

    myFileObject.close()
    #cmds.playbackOptions(e=1, min=minTime, max=maxTime)


class NagaPipeline(object):

    def __init__(self):
        print("NagaPipeline::__init__")
        self.created = True
        self._init()
        self._createUI()
        self.webSock = MayaWebSocket.MayaWebSocket()
        self.lastSyncTime = time.time()
        self.uiCallback = OMUI.MUiMessage.addUiDeletedCallback(
            self.myWindow, uiDeleteCallback, self)

    def __del__(self):
        if not self.created:
            return
        print("NagaPipeline::__del__")
        OM.MMessage.removeCallback(self.uiCallback)
        self.disconnect_to_game_server()
        self.created = False

    def _init(self):
        self.callbacks = []

        fov = getCameraFov('persp')
        print(fov)

        nagaDir = os.environ['NAGA_DIR']
        nagaDir = nagaDir.replace("\\", "/")
        self.nagaPath = nagaDir
        self.pipelinePath = nagaDir + 'Pipeline/'
        self.hkoPath = self.pipelinePath + 'havok_hko/'
        self.havokPakPath = 'Data/havok_packages/'
        self.havokExportPath = nagaDir + self.havokPakPath
        self.lastOutputName = ''
        self.havokNodePath = 'Data/havok_packages/'
        self.engineScale = 0.01

    def _addAttCallback(self, name):
        callbackId = OM.MNodeMessage.addAttributeChangedCallback(
            nameToNode(name), attrChangedCallback, self)
        self.callbacks.append(callbackId)
        print("add callback" + str(callbackId))

    def _clearAttCallbacks(self):
        for cb in self.callbacks:
            print("remove callback" + str(cb))
            OM.MMessage.removeCallback(cb)
        self.callbacks = []

    #
    #
    #   GUI FUNCTIONS
    #
    #
    def _createUI(self):
        self.myUI = 'Naga_UI'
        if cmds.window(self.myUI, exists=True):
            cmds.deleteUI(self.myUI)

        self.myWindow = cmds.window(self.myUI,
                                    t='Pipeline')

        def uiExitFunc(*args):
            cmds.deleteUI(self.myUI)

        # Create menu bar layout
        self.uiMenuBar = cmds.menuBarLayout('nagaMenuBar')
        cmds.menu(label='File')
        cmds.menuItem(label='Exit', command=uiExitFunc)
        cmds.menu(label='Help', helpMenu=True)
        cmds.menuItem(label='About...')

         # Create tabs layout
        self.uiForm = cmds.formLayout('nagaForm', p=self.uiMenuBar)
        self.uiTAB = cmds.tabLayout(
            'Scene', innerMarginWidth=5, innerMarginHeight=5)
        cmds.formLayout(self.uiForm, edit=True,
                        attachForm=((self.uiTAB, 'top', 20),
                                    (self.uiTAB, 'left', 0),
                                    (self.uiTAB, 'bottom', 0),
                                    (self.uiTAB, 'right', 0)))

        # Each rowColumn in Global Settings
        # RC 01 Global Settings
        uiRC01 = cmds.rowColumnLayout(
            numberOfColumns=2, cw=[(1, 15), (2, 400)], p=self.uiForm)
        cmds.formLayout(self.uiForm, e=True, attachForm=(uiRC01, 'top', 10))
        cmds.text(' ')
        cmds.text("NAGA Pipeline")

        self.sceneTab = cmds.paneLayout(
            'Export', configuration='horizontal2',
            p=self.uiTAB)

        cmds.rowColumnLayout(numberOfColumns=2,
                             cw=[(1, 200), (2, 200)])
        
        # column 1
        cmds.text(label='output file name:')
        defaultOutputName = getSceneName() + ".hkx"
        self.outTextField = cmds.textField(
            'Naga_Output_Text', text=defaultOutputName)

        # column 2
        cmds.text('export type:')
        self.hkoMenuGrp = cmds.optionMenuGrp('HKO_List')
        for hkoName in HKO_NAMES:
            cmds.menuItem(label=hkoName)

        # column 3
        self.selectCheck = cmds.checkBox(label='Select Only', v=False)
        self.syncCheck = cmds.checkBox(label='RealTime Sync', v=True)

        # column 4
        cmds.button('Export!', c=self.onExportButtonClicked)
        cmds.button('Preview!', c=self.onPreviewButtonClicked)

        cmds.showWindow(self.myUI)

    #
    #
    #   INNER FUNCTIONS
    #
    #

    def lunchBat(self, batName, batFolder, wait=False):
        print("bat lunch name %s, folder %s, " % (batName, batFolder))
        p = Popen(batFolder + batName, cwd=batFolder)
        if(wait):
            stdout, stderr = p.communicate()
            print(stdout)
            print(stderr)

    def onExportButtonClicked(self, *arg):
        self.havokExport(self.getHKOSelectIndex(), self.isSelectOnly())

    def onPreviewButtonClicked(self, *arg):
        filePath = os.environ['NAGA_DIR']
        fileName = filePath + 'hkxSceneViewer.bat'
        hkxFile = self.havokNodePath + self.lastOutputName
        args = [fileName, '-havokfile', hkxFile]
        Popen(args, cwd=filePath)
        time.sleep(2)
        self.connect_to_game_server()

    def isSyncChecked(self):
        return cmds.checkBox(self.syncCheck, q=1, v=1)

    def isSelectOnly(self):
        return cmds.checkBox(self.selectCheck, q=1, v=1)

    def havokExport(self, hkoType, selectOnly):
        outputText = cmds.textField(self.outTextField, q=1, tx=1)
        if (outputText != ''):
            ouputFileName = self.havokExportPath + outputText
            self.lastOutputName = outputText
            self.exportToHKX(hkoFileName=HKO_FILES[hkoType],
                             outFileName=ouputFileName,
                             rig=self.pipelinePath + 'monk_rig.txt',
                             s=selectOnly)
        else:
            cmds.error('output file is empty or export type is null!')

    def exportToHKX(self, hkoFileName, outFileName, rig='', arg='', s=False):
        hkoFullPath = self.hkoPath + hkoFileName
        print("hko file = " + hkoFullPath)
        print("out file = " + outFileName)

        # -v means visible only.
        eval_cmd = "hkCmdExportScene -o \"" + hkoFullPath + "\" -b -v "
        if s:
            eval_cmd += "-s "
        eval_cmd += "-ev "
        envCmd = "HK_OUTPUT=" + outFileName + ";"
        # set workspace to enviroment
        workSpace = cmds.workspace(q=True, dir=True, rd=True)
        envCmd += "WORK_SPACE=" + workSpace + ";"
        if(arg):
            envCmd += arg
        eval_cmd += '"' + envCmd + '"'
        print(eval_cmd)

        sceneDir = getSceneDirectory()
        print("scene dir = " + sceneDir)
        tmpRigFile = sceneDir + "\\output_rig.txt"

        if(rig):
            shutil.copyfile(rig, tmpRigFile)

        mel.eval(eval_cmd)

    def connect_to_game_server(self):
        self._clearAttCallbacks()
        self.webSock.connect(self.onWebSocketOpen)
        if(self.isSyncChecked()):
            self._addAttCallback('persp')
            selection = cmds.ls(sl=True)
            for sel in selection:
                if(sel != 'persp'):
                    self._addAttCallback(sel)

    def disconnect_to_game_server(self):
        self._clearAttCallbacks()
        self.webSock.disconnect()

    def onWebSocketOpen(self):
        print("\n\nonWebSocketOpen\n\n")

    def remoteSyncTransform(self, nodeName, minTime=0.05):
        curTime = time.time()
        dt = curTime - self.lastSyncTime
        if(dt < minTime):
            return
        self.lastSyncTime = curTime
        translate = cmds.getAttr(nodeName + '.translate')[0]
        translate = (translate[0], translate[1], -1 * translate[2])
        rotate = cmds.getAttr(nodeName + '.rotate')[0]
        euler = OM.MEulerRotation(-math.radians(rotate[0]),
                                  -math.radians(rotate[1]),
                                  -math.radians(rotate[2]),
                                  cmds.getAttr(nodeName + '.rotateOrder'))
        euler.reorderIt(OM.MEulerRotation.kZXY)
        rotate = (math.degrees(euler.x),
                  math.degrees(euler.y),
                  math.degrees(euler.z))
        senddata = '%g %g %g,%g %g %g' % (translate[0] * self.engineScale,
                                          translate[1] * self.engineScale,
                                          translate[2] * self.engineScale,
                                          rotate[0],
                                          rotate[1],
                                          rotate[2])
        # print(senddata)
        self.webSock.sendmayacommand(nodeName + "_transform", senddata)

    def refreshPoseList(self):
        self.poseList = osGetFileList(
            self.pipelinePath + 'import_keys/', '.fbx')
        menuName = self.poseMenuGrp + '|OptionMenu'
        clearMenu(menuName)
        for pose in self.poseList:
            cmds.menuItem(label=pose, p=menuName)

    def getHKOSelectIndex(self):
        return cmds.optionMenuGrp(self.hkoMenuGrp, q=1, sl=1) - 1
