import os
import maya.cmds as cmds
import maya.mel as mel
import subprocess
import math
import sys


UI_NAME = 'Naga_UI'


def lunchApplication(name, folder, args, wait=False):
    print('lunch name = ' + name + ', folder = ' + folder)
    path = folder + name
    cmdArgs = args
    cmdArgs.insert(0, path)
    print(cmdArgs)
    p = subprocess.Popen(cmdArgs, cwd=folder)
    if(wait):
        stdout, stderr = p.communicate()
        print(stdout)
        print(stderr)


def getCameraFov(cameraShapeName='perspShape'):
    aperture = cmds.getAttr(cameraShapeName + '.hfa')
    fl = cmds.getAttr(cameraShapeName + '.focalLength')
    fov = aperture * 0.5 / (fl * 0.03937)
    fov = 2.0 * math.atan(fov) / 3.14159 * 180.0
    return fov


def getSceneName():
    fileName = cmds.file(q=True, sn=True)
    print("current scene = " + fileName)
    fileName = os.path.basename(fileName)
    if(not fileName):
        cmds.warning('not named scene!')
        return 'untitiled'
    (prefix, sep, suffix) = fileName.rpartition('.')
    return prefix


def getSceneDirectory():
    fileName = cmds.file(q=True, sn=True)
    print("current scene = " + fileName)
    return os.path.dirname(fileName)


def osGetFileList(directory, ext):
    fileList = []
    for root, dirs, files in os.walk(directory):
        for name in files:
            lowerName = name.lower()
            if lowerName.endswith(ext):
                path = os.path.join(root, name)
                path = path.replace('\\', '/')
                fileList.append(path)
    return fileList


def fixAssemblyRepPath():
    nodeList = cmds.ls(type='assemblyDefinition')
    for node in nodeList:
        dataAttrib = node + '.representations[0].repData'
        data = cmds.getAttr(dataAttrib)
        # FIXME just hack with c:/ d:/ ... h:/ start
        disk_list = ['C', 'D', 'E', 'F', 'G', 'H']
        for disk in disk_list:
            if data.toLower().startswith(disk):
                pos = data.find('/LevelData') + 1
                strlen = len(data)
                data = data[pos: strlen]
                print(data)
                cmds.setAttr(dataAttrib, data, type='string')


def fixAssemblyTransform():
    node = cmds.ls(sl=True)[0]
    cmds.setAttr(node + '.translate', 0, 0, 0, type='float3')
    cmds.setAttr(node + '.rotate', 0, 0, 0, type='float3')
    cmds.setAttr(node + '.scale', 1, 1, 1, type='float3')


def getAD_EntityType(node):
    dataAttrib = node + '.representations[0].repData'
    repData = cmds.getAttr(dataAttrib)
    base = os.path.basename(repData)
    return os.path.splitext(base)[0]


def openAD_Reference():
    node = cmds.ls(sl=True)[0]
    nodeType = cmds.nodeType(node)
    if(nodeType != 'assemblyDefinition'):
        node = cmds.listRelatives(node, parent=True)[0]
    repData = cmds.getAttr(node + '.representations[0].repData')
    print(repData)
    workSpace = cmds.workspace(q=True, dir=True, rd=True)
    refFile = os.path.join(workSpace, repData)
    print(refFile)
    cmds.file(save=True)
    cmds.file(refFile, open=True)


def fbx_export(output_filename):
    mel.eval("FBXExportSmoothingGroups -v true")
    #mel.eval("FBXExportHardEdges -v false")
    #mel.eval("FBXExportTangents -v false")
    mel.eval("FBXExportSmoothMesh -v true")
    #mel.eval("FBXExportInstances -v false")
    #mel.eval("FBXExportReferencedContainersContent -v false")
    # Animation
    #mel.eval("FBXExportBakeComplexAnimation -v true")
    #mel.eval("FBXExportBakeComplexStart -v "+str(exportStartFrame[x]))
    #mel.eval("FBXExportBakeComplexEnd -v "+str(exportEndFrame[x]))
    #mel.eval("FBXExportBakeComplexStep -v 1")
    # mm.eval("FBXExportBakeResampleAll -v true")
    #mel.eval("FBXExportUseSceneName -v false")
    #mel.eval("FBXExportQuaternion -v euler")
    mel.eval("FBXExportShapes -v true")
    mel.eval("FBXExportSkins -v true")
    # Constraints
    mel.eval("FBXExportConstraints -v false")
    # Cameras
    mel.eval("FBXExportCameras -v true")
    # Lights
    mel.eval("FBXExportLights -v true")
    # Embed Media
    #mel.eval("FBXExportEmbeddedTextures -v true")
    # Connections
    #mel.eval("FBXExportInputConnections -v false")
    # Axis Conversion
    mel.eval("FBXExportUpAxis y")
    # Export!
    mel.eval("FBXExport -f " + output_filename + ".fbx -s")


class NagaPipeline(object):
    NagaObject = None

    def __del__(self):
        print('__del__')

    def create(self):
        self.callbacks = []
        self._createUI()
        self.created = True
        self.lastMayaScene = ''
        cmds.scriptJob(parent=self.myWindow, cu=False, ro=False,
                       event=('SceneOpened', self.onSceneChanged))
        cmds.scriptJob(parent=self.myWindow, cu=False, ro=False,
                       event=('SceneSaved', self.onSceneChanged))
        self.nagaDir = os.environ['NAGA_DIR']
        self.binDir = self.nagaDir + '/Application'
        self.dataDir = self.binDir + '/Data'

    def destroy(self):
        if not self.created:
            return
        if cmds.window(UI_NAME, exists=True):
            cmds.deleteUI(UI_NAME)

    #
    # Callbacks
    #
    def onSceneChanged(self):
        self.updateUIByData()

    #
    # GUI FUNCTIONS
    #
    def _createUI(self):

        if cmds.window(UI_NAME, exists=1):
            cmds.deleteUI(UI_NAME)

        self.myWindow = cmds.window(UI_NAME, t='Pipeline')
        cmds.columnLayout(cal='center', adj=1)

        cmds.text(label='Export Name', align='center')
        displayName = '*** %s ***' % getSceneName()
        self.nameText = cmds.text(label=displayName,
                                  align='center',
                                  bgc=[0, 1, 0],
                                  h=30)

        cmds.setParent('..')

        self.exportTypeGrp = cmds.optionMenuGrp('ExportType', l='type:')
        cmds.menuItem(label='model')
        cmds.menuItem(label='scene')
        cmds.menuItem(label='animation')
        cmds.setParent('..')

        cmds.frameLayout(l="Assembly Util", cll=1)
        # cmds.rowLayout(nc=2)
        cmds.button('Fix Assembly Path', c=self.onFixPathClicked)
        cmds.button('Open Selection AR', c=self.onOpenARClicked)
        cmds.button('Back To Last Level', c=self.onBackLevelClicked)
        cmds.setParent('..')
        cmds.setParent('..')
        cmds.setParent('..')

        height = 75
        margin_w = 5
        margin_h = 5
        cmds.frameLayout(
            l="Export", cll=1, mh=margin_h, mw=margin_w)
        cmds.button('EXPORT', h=height, bgc=[0, 1, 1],
                    c=self.onExportButtonClicked)
        cmds.setParent('..')
        cmds.showWindow(UI_NAME)
        self.updateUIByData()

    def isSelectOnly(self):
        return cmds.checkBox(self.selectCheck, q=1, v=1)

    def onFixPathClicked(self):
        fixAssemblyRepPath()

    def onOpenARClicked(self, *arg):
        self.lastMayaScene = cmds.file(q=True, sn=True)
        openAD_Reference()

    def onBackLevelClicked(self, *arg):
        if(not self.lastMayaScene):
            return
        cmds.file(mf=0)
        cmds.file(self.lastMayaScene, o=True)
        self.lastMayaScene = ''

    def onExportButtonClicked(self, *arg):
        self.export(getSceneName())

    def updateUIByData(self):
        #
        displayName = '*** %s ***' % getSceneName()
        cmds.text(self.nameText, e=1, label=displayName)

    def getExportType(self):
        return cmds.optionMenuGrp(self.exportTypeGrp, v=1, sl=1)
    #
    # UTIL FUNCTIONS
    #

    def export(self, exportName):
        pass
        #


def clean():
    if cmds.window(UI_NAME, exists=True):
        cmds.deleteUI(UI_NAME)
    if NagaPipeline.NagaObject:
        NagaPipeline.NagaObject.destroy()
    NagaPipeline.NagaObject = None


def create():
    pipe = NagaPipeline()
    pipe.create()
    NagaPipeline.NagaObject = pipe
