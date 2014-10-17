import MayaWebSocket as WEB
reload(WEB)
import NagaMayaUtil as NAGA
reload(NAGA)
import maya.cmds as cmds
import maya.mel as mel
import maya.OpenMaya as OM
import maya.OpenMayaUI as OMUI
import time
import os

PREVIEW_PACK = 'preview'
GAME_APP = 'Game_Debug'
UI_NAME = 'Naga_UI'


class NagaPipeline(object):
    NagaObject = None

    def __del__(self):
        print('__del__')

    def create(self):
        self.callbacks = []
        # print("########### NagaPipeline::create start ##################")
        self.naga = NAGA.NagaMayaUtil()
        self.engineScale = 0.01
        self.lastSyncCallback = None
        # GUI
        self._createUI()
        # WEB
        self.webSock = WEB.MayaWebSocket()
        self.connect_to_game_server()
        self.created = True
        cmds.scriptJob(parent=self.myWindow, cu=False, ro=False,
                       event=('SceneOpened', self.onSceneChanged))
        cmds.scriptJob(parent=self.myWindow, cu=False, ro=False,
                       event=('SceneSaved', self.onSceneChanged))
        # print("########### NagaPipeline::create end ##################")

    def destroy(self):
        if not self.created:
            return
        if cmds.window(UI_NAME, exists=True):
            cmds.deleteUI(UI_NAME)
        # print("########### NagaPipeline::destroy start ##################")
        self.disconnect_to_game_server()
        self.created = False
        # print("########### NagaPipeline::destroy end ##################")

    #
    # Callbacks
    #
    def onSceneChanged(self):
        displayName = '*** %s ***' % NAGA.getSceneName()
        cmds.text(self.nameText, e=1, label=displayName)

    #
    # GUI FUNCTIONS
    #
    def _createUI(self):

        if cmds.window(UI_NAME, exists=1):
            cmds.deleteUI(UI_NAME)

        self.myWindow = cmds.window(UI_NAME, t='Pipeline')
        cmds.columnLayout(cal='center', adj=1)

        #cmds.frameLayout(l='Export Name', cll=1, h=50)
        cmds.text(label='Export Name', align='center')
        displayName = '*** %s ***' % NAGA.getSceneName()
        self.nameText = cmds.text(label=displayName,
                                  align='center',
                                  bgc=[0, 1, 0],
                                  h=30)

        cmds.frameLayout(l="Export Parameters", cll=1)
        self.selectCheck = cmds.checkBox(label='Export Select Only', v=False)
        self.hkoTypeGroup = cmds.optionMenuGrp('HkoType', l='type:')
        for hkoType in self.naga.getHkoList():
            hkoType = os.path.basename(hkoType)
            cmds.menuItem(label=hkoType)
        self.rigTypeGroup = cmds.optionMenuGrp('RigType', l='rig:')
        for rigType in self.naga.getRigList():
            rigName = os.path.basename(rigType)
            rigName = rigName[:-6]
            cmds.menuItem(label=rigName)
        self.packageGroup = cmds.optionMenuGrp('PackageName', l='package:')
        for packageName in self.naga.getPackageList():
            cmds.menuItem(label=packageName)

        cmds.setParent('..')

        cmds.frameLayout(l="Util", cll=1)
        cmds.rowLayout(nc=2)
        cmds.button('Open Selection AR', c=self.onOpenARClicked)
        cmds.button('Back To Last Level', c=self.onBackLevelClicked)
        cmds.setParent('..')
        cmds.rowLayout(nc=2)
        cmds.button('Add Animation Trigger Node', c=self.onAddTriggerClicked)
        cmds.button('Add Proxy Node', c=self.onAddProxyClicked)
        cmds.setParent('..')
        cmds.rowLayout(nc=2)
        cmds.button('Add Script', c=self.onAddScriptClicked)
        cmds.setParent('..')
        cmds.setParent('..')

        height = 75
        margin_w = 5
        margin_h = 5
        cmds.frameLayout(
            l="Preview and Export", cll=1, mh=margin_h, mw=margin_w)
        cmds.button('Preview', h=height, bgc=[1, 1, 0],
                    c=self.onPreviewButtonClicked)
        cmds.button('Export', h=height, bgc=[0, 1, 1],
                    c=self.onExportButtonClicked)
        cmds.setParent('..')
        cmds.showWindow(UI_NAME)

    def onPreviewButtonClicked(self, *arg):
        self.preview(NAGA.getSceneName())

    def isSelectOnly(self):
        return cmds.checkBox(self.selectCheck, q=1, v=1)

    def onOpenARClicked(self, *arg):
        self.lastMayaScene = cmds.file(q=True, sn=True)
        NAGA.openAD_Reference()

    def onBackLevelClicked(self, *arg):
        if(not self.lastMayaScene):
            return
        cmds.file(mf=0)
        cmds.file(self.lastMayaScene, o=True)

    def onExportButtonClicked(self, *arg):
        self.export(NAGA.getSceneName())

    def onAddTriggerClicked(self, *arg):
        NAGA.createTriggerNode()

    def onAddProxyClicked(self, *arg):
        NAGA.createProxyNode()

    def onAddScriptClicked(self, *arg):
        NAGA.createScriptNode()

    #
    # UTIL FUNCTIONS
    #
    def doExport(self, exportName, packageName, hkoType=0, rigName=''):
        # step1 : export use havok plugin.
        self.naga.exportToHKX(
            exportName, packageName, hkoType, rig=rigName, arg='',
            s=self.isSelectOnly())

        # step2 : convert the hkx to intermediate data
        # using havok converter
        # step3: lunch data-compiler to convert intermediate to finally package
        self.naga.convertHkx(exportName, packageName, bDebug=False)

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

        rigIndex = cmds.optionMenuGrp(self.rigTypeGroup, q=1, sl=1) - 1
        rigName = self.naga.getRigList()[rigIndex]
        rigName = os.path.basename(rigName)
        hkoIndex = cmds.optionMenuGrp(self.hkoTypeGroup, q=1, sl=1) - 1

        self.doExport(exportName,
                      packageName,
                      hkoType=hkoIndex,
                      rigName=rigName)

        if not self.webSock.connected:
            self.lunchEngine(packageName, debug=1)
            time.sleep(0.2)
        else:
            self.reloadCompileResult()

    def export(self, exportName):

        packageIndex = cmds.optionMenuGrp(self.packageGroup, q=1, sl=1) - 1
        packageName = self.naga.getPackageList()[packageIndex]

        packageName = packageName
        rigIndex = cmds.optionMenuGrp(self.rigTypeGroup, q=1, sl=1) - 1
        rigName = self.naga.getRigList()[rigIndex]
        rigName = os.path.basename(rigName)
        hkoIndex = cmds.optionMenuGrp(self.hkoTypeGroup, q=1, sl=1) - 1

        self.doExport(exportName,
                      packageName,
                      hkoType=hkoIndex,
                      rigName=rigName)

    def lunchEngine(self, packageName, debug=False):
        sceneName = NAGA.getSceneName()
        width = 800
        height = 600
        args = ['--websocket',
                '--package', 'data/' + packageName + '.package',
                '--script', 'core/scripts/preview',
                '-w', str(width),
                '-h', str(height)]

        if(NAGA.isLevel(sceneName)):
            print('preview ---- level')
            previewName = packageName + '/' + sceneName
            args.append('--level')
            args.append(previewName)
        elif(self.isAnimationType()):
            print('preview ---- animation')
            # add animation
            previewName = packageName + '/actor/' + sceneName
            args.append('--animation')
            args.append(previewName)
            # add rig actor
            rigIndex = cmds.optionMenuGrp(self.rigTypeGroup, q=1, sl=1) - 1
            rigName = self.naga.getRigList()[rigIndex]
            rigName = os.path.basename(rigName)
            rigName = rigName[:-6]
            rigName = packageName + '/actor/' + rigName

            args.append('--actor')
            args.append(rigName)
        else:
            print('preview ---- actor')
            previewName = packageName + '/actor/' + sceneName
            args.append('--actor')
            args.append(previewName)
        if(debug):
            args.append('--debug')
        NAGA.lunchApplication(GAME_APP, self.naga.appPath, args, False)

    def isAnimationType(self):
        hkoList = self.naga.getHkoList()
        hkoIndex = cmds.optionMenuGrp(self.hkoTypeGroup, q=1, sl=1) - 1
        hkoFile = hkoList[hkoIndex]
        return hkoFile.find('animation') != -1

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
        pass

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
    if cmds.window(UI_NAME, exists=True):
        cmds.deleteUI(UI_NAME)
    if NagaPipeline.NagaObject:
        NagaPipeline.NagaObject.destroy()
    NagaPipeline.NagaObject = None


def create():
    pipe = NagaPipeline()
    pipe.create()
    NagaPipeline.NagaObject = pipe


def test():
    NagaPipeline.NagaObject = None
