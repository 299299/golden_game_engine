import MayaWebSocket as WEB
reload(WEB)
import NagaMayaUtil as NAGA
reload(NAGA)
import maya.cmds as cmds
import maya.OpenMaya as OM
import maya.OpenMayaUI as OMUI
import math
import time
import os


def nameToNode(name):
    selectionList = OM.MSelectionList()
    selectionList.add(name)
    node = OM.MObject()
    selectionList.getDependNode(0, node)
    return node


def attrChangedCallback(msg, mplug, otherMplug, pipe):
    if not (msg & OM.MNodeMessage.kAttributeSet):
        return
    nodeName, attrName = mplug.name().split('.')
    if nodeName == 'persp':
        if(pipe.isCameraSync()):
            pipe.remoteSyncCamera()
    else:
        pipe.remoteSyncTransform(nodeName)


def sceneOpenedCallback(pipe):
    pipe.updateSceneTitle()


def sceneSavedCallback(pipe):
    pipe.updateSceneTitle()


def uiDeleteCallback(pipe):
    print("ui delete callback")
    pipe.destroy()
    NagaPipeline.NagaObject = None


PREVIEW_PACK = 'preview'
GAME_APP = 'Game_Debug'


class NagaPipeline(object):
    NagaObject = None

    def __del__(self):
        print('__del__')

    def create(self):
        # print("########### NagaPipeline::create start ##################")
        self.callbacks = []
        self.naga = NAGA.NagaMayaUtil()
        self.engineScale = 0.01
        # GUI
        self._loadSettings()
        self._createUI()
        self.saveCallback = OM.MSceneMessage.addCallback(
            OM.MSceneMessage.kAfterOpen, sceneSavedCallback, self)
        self.openCallback = OM.MSceneMessage.addCallback(
            OM.MSceneMessage.kAfterSave, sceneOpenedCallback, self)
        self.uiCallback = OMUI.MUiMessage.addUiDeletedCallback(
            self.myWindow, uiDeleteCallback, self)

        self._addAttCallback('persp')
        # WEB
        self.webSock = WEB.MayaWebSocket()
        self.lastSyncTime = time.time()
        self.connect_to_game_server()
        self.created = True
        # print("########### NagaPipeline::create end ##################")

    def destroy(self):
        if not self.created:
            return
        # print("########### NagaPipeline::destroy start ##################")
        self._clearAttCallbacks()
        if(self.openCallback):
            OM.MMessage.removeCallback(self.openCallback)
        if(self.saveCallback):
            OM.MMessage.removeCallback(self.saveCallback)
        self.disconnect_to_game_server()
        self.created = False
        # print("########### NagaPipeline::destroy end ##################")

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

    def _loadSettings(self):
        self.settings = dict()
        self.settings.clear()
        fileName = NAGA.getMayaScriptPath() + 'setting.ini'
        print(fileName)
        if(not os.path.exists(fileName)):
            return
        f = open(fileName, 'r')
        lines = f.readlines()
        for line in lines:
            line = line.strip('\n')
            nameList = line.split('=')
            key = nameList[1]
            value = nameList[0]
            print(key + '=' + value)
            self.settings[key] = value
        key = 'nagaPath'
        if(key in self.settings):
            self.naga.onNagaPathChanged(self.settings[key])

    def _saveSettings(self):
        fileName = NAGA.getMayaScriptPath() + 'setting.ini'
        print(fileName)
        f = open(fileName, 'w')
        for key, value in self.settings.items():
            line = '%s=%s\n' % (key, value)
            f.write(line)
        f.close()

    #
    # Callbacks
    #

    def updateSceneTitle(self):
        displayName = '*** %s ***' % NAGA.getSceneName()
        cmds.text(self.nameText, e=1, label=displayName)

    #
    # GUI FUNCTIONS
    #
    def _createUI(self):
        uiName = 'Naga_UI'
        if cmds.window(uiName, exists=True):
            cmds.deleteUI(uiName)

        self.myWindow = cmds.window(uiName, t='Pipeline')
        cmds.columnLayout(cal='center', adj=True)

        cmds.frameLayout(l='Export Name', cll=1, h=50)
        displayName = '*** %s ***' % NAGA.getSceneName()
        self.nameText = cmds.text(label=displayName,
                                  align='center',
                                  bgc=[0, 1, 0])
        cmds.setParent('..')

        cmds.frameLayout(l="Parameters", cll=1, h=50)
        cmds.rowLayout(numberOfColumns=2)
        self.selectCheck = cmds.checkBox(label='Export Select Only', v=False)
        self.cameraCheck = cmds.checkBox(label='Remote Sync Camera', v=True)
        cmds.setParent('..')
        cmds.setParent('..')

        cmds.frameLayout(l="Engine Parameters", cll=1, h=50)
        cmds.rowLayout(numberOfColumns=2)
        self.filePath = cmds.textField(w=300, ed=True, text=self.naga.nagaPath)
        cmds.button(label="Browse...", w=75, c=self.fileExplorer)
        cmds.setParent('..')
        cmds.setParent('..')

        height = 30
        margin_w = 5
        margin_h = 5
        cmds.frameLayout(
            l="Level Helper", cll=1, mh=margin_h, mw=margin_w)
        cmds.button('Open Selection AR', h=height, c=self.onOpenARClicked)
        cmds.button('Back To Last Level', h=height, c=self.onBackLevelClicked)
        cmds.setParent('..')
        cmds.setParent('..')

        cmds.frameLayout(
            l="Engine Remote", cll=1, mh=margin_h, mw=margin_w)
        cmds.button('Close Engine', h=height, c=self.onCloseEngineClicked)
        cmds.button('ReOpen Engine', h=height, c=self.onReopenEngineClicked)
        cmds.setParent('..')
        cmds.setParent('..')

        cmds.frameLayout(l="Animation", cll=1, mh=2, mw=2)
        cmds.rowLayout(numberOfColumns=3)
        animation_types = [
            'default',
            'root-motion-no-rotation',
            'root-motion-rotation',
            'additive-first-frame',
        ]
        cmds.text(label='export type:', align='center', bgc=[0, 1, 0])
        self.animTypeGroup = cmds.optionMenuGrp('AnimType')
        for animType in animation_types:
            cmds.menuItem(label=animType)
        cmds.button('Export', h=height, c=self.onAnimExportClicked)
        cmds.setParent('..')
        cmds.setParent('..')
        cmds.setParent('..')

        height = 75
        cmds.frameLayout(
            l="Preview and Export", cll=1, mh=margin_h, mw=margin_w)
        cmds.button('Preview', h=height, bgc=[1, 1, 0],
                    c=self.onPreviewButtonClicked)
        cmds.setParent('..')
        cmds.showWindow(uiName)

    def onPreviewButtonClicked(self, *arg):
        self.preview(NAGA.getSceneName())

    def isSelectOnly(self):
        return cmds.checkBox(self.selectCheck, q=1, v=1)

    def isCameraSync(self):
        return cmds.checkBox(self.cameraCheck, q=1, v=1)

    def onOpenARClicked(self, *arg):
        self.lastMayaScene = cmds.file(q=True, sn=True)
        NAGA.openAD_Reference()

    def onBackLevelClicked(self, *arg):
        if(not self.lastMayaScene):
            return
        cmds.file(mf=0)
        cmds.file(self.lastMayaScene, o=True)

    def onCloseEngineClicked(self, *arg):
        self.webSock.sendmayacommand('exit')

    def onReopenEngineClicked(self, *arg):
        self.reOpenEngine()

    def fileExplorer(self, *arg):
        filename = cmds.fileDialog2(fm=3, caption="Engine Path")
        if not filename:
            return
        self.naga.onNagaPathChanged(filename[0])
        cmds.textField(self.filePath, e=1, text=self.naga.nagaPath)
        key = 'nagaPath'
        value = self.naga.nagaPath
        if(key in self.settings):
            dct = {key: value}
            self.settings.update(dct)
        else:
            self.settings[key] = value
        self._saveSettings()

    def onAnimExportClicked(self, *arg):
        exportName = NAGA.getSceneName()
        packageName = 'Animation'
        index = cmds.optionMenuGrp(self.animTypeGroup, q=1, sl=1) - 2
        self.export(exportName, packageName, index)

    #
    # UTIL FUNCTIONS
    #

    def reOpenEngine(self, timeToWait=1):
        self.webSock.sendmayacommand('exit')
        time.sleep(timeToWait)
        width = 800
        height = 600
        args = ['-m', '1', '-w', str(width), '-h', str(height)]
        NAGA.lunchApplication(GAME_APP, self.naga.appPath, args, False)

    def export(self, exportName, packageName, hkoType=0):
        # step1 : export use havok plugin.
        self.naga.exportToHKX(
            exportName, packageName, hkoType, '', '', s=self.isSelectOnly())

        # step2 : convert the hkx to intermediate data
        # using havok converter
        # step3: lunch data-compiler to convert intermediate to finally package
        self.naga.convertHkx(exportName, packageName)

    def reloadCompileResult(self):
        if not self.webSock.connected:
            return
        fileName = self.naga.appPath + 'data_compiler_result.txt'
        if not os.path.exists(fileName):
            return
        f = open(fileName, 'r')
        lines = f.readlines()
        for line in lines:
            theLine = line[0:len(line) - 2]
            print('reload ' + theLine)
            self.webSock.sendmayacommand('reload_resource_file', theLine)

    def preview(self, exportName):
        if(NAGA.isLevel(exportName)):
            # validate level
            proxyNum, packageName = self.naga.addLevelProxy()
            if proxyNum <= 0:
                cmds.error('add level proxy failed!')
                return
        else:
            packageName = PREVIEW_PACK
        self.export(exportName, packageName)

        if not self.webSock.connected:
            self.lunchEngine(packageName)
            time.sleep(0.2)
        else:
            self.reloadCompileResult()

    def remoteSyncTransform(self, nodeName, minTime=0.05):
        curTime = time.time()
        dt = curTime - self.lastSyncTime
        if(dt < minTime):
            return
        self.lastSyncTime = curTime
        translate = cmds.getAttr(nodeName + '.translate')[0]
        translate = (translate[0], translate[1], translate[2])
        rotate = cmds.getAttr(nodeName + '.rotate')[0]
        euler = OM.MEulerRotation(math.radians(rotate[0]),
                                  math.radians(rotate[1]),
                                  math.radians(rotate[2]),
                                  cmds.getAttr(nodeName + '.rotateOrder'))
        rotate = (euler.x, euler.y, euler.z)
        senddata = '%g,%g,%g,%g,%g,%g' % (translate[0] * self.engineScale,
                                          translate[1] * self.engineScale,
                                          translate[2] * self.engineScale,
                                          math.radians(rotate[0]),
                                          math.radians(rotate[1]),
                                          math.radians(rotate[1]))
        self.webSock.sendmayacommand(nodeName + "_transform", senddata)

    def remoteSyncCamera(self, minTime=0.05):
        curTime = time.time()
        dt = curTime - self.lastSyncTime
        if(dt < minTime):
            return
        self.lastSyncTime = curTime
        self.doSyncRemoteCamera()

    def doSyncRemoteCamera(self):
        nodeName = 'persp'
        #translate = cmds.getAttr(nodeName + '.translate')[0]
        #lookAt = cmds.camera(nodeName, q=True, wci=True)
        #rotate = cmds.getAttr(nodeName + '.rotate')[0]
        matrix = cmds.xform(nodeName, q=True, m=True, ws=True)
        fov = NAGA.getCameraFov()
        senddata = '%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g'\
            % (fov,
               matrix[0], matrix[1], matrix[2], matrix[3],
               matrix[4], matrix[5], matrix[6], matrix[7],
               matrix[8], matrix[9], matrix[10], matrix[11],
               matrix[12], matrix[13], matrix[14], matrix[15])
        #print(senddata)
        self.webSock.sendmayacommand("camera_transfrom", senddata)

    def lunchEngine(self, packageName):
        sceneName = NAGA.getSceneName()
        width = 800
        height = 600
        if(NAGA.isLevel(sceneName)):
            previewName = packageName + '/' + sceneName
            args = ['-m', '1', '--level',
                    previewName, '-w', str(width), '-h', str(height)]
        else:
            previewName = packageName + '/entity/' + sceneName
            args = ['-m', '1', '--entity',
                    previewName, '-w', str(width), '-h', str(height)]
        NAGA.lunchApplication(GAME_APP, self.naga.appPath, args, False)

    #
    # WEB SOCKET FUNCTIONS
    #
    def connect_to_game_server(self):
        self.webSock.connect(self.onWebSocketOpen,
                             self.onWebSocketMessage,
                             self.onWebSocketClosed)

    def disconnect_to_game_server(self):
        self.webSock.disconnect()

    def onWebSocketOpen(self):
        self.doSyncRemoteCamera()

    def onWebSocketMessage(self, json_object):
        type_name = json_object['type']
        if type_name == 'logging.msg':
            print('[ENGINE LOG] ' + str(json_object['msg']))
        else:
            pass

    def onWebSocketClosed(self):
        # print('\n\nonWebSocketClosed\n\n')
        pass


def clean():
    uiName = 'Naga_UI'
    if cmds.window(uiName, exists=True):
        cmds.deleteUI(uiName)
    if NagaPipeline.NagaObject:
        NagaPipeline.NagaObject.destroy()
    NagaPipeline.NagaObject = None


def create():
    pipe = NagaPipeline()
    pipe.create()
    NagaPipeline.NagaObject = pipe


def test():
    NagaPipeline.NagaObject = None
