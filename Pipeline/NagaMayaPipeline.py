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
DEBUG = True


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

        NAGA.createHistoryNode()
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
        for rigName in self.naga.getRigList():
            cmds.menuItem(label=rigName)
        self.packageGroup = cmds.optionMenuGrp('PackageName', l='package:')
        for packageName in self.naga.getPackageList():
            cmds.menuItem(label=packageName)

        cmds.setParent('..')

        cmds.frameLayout(l="Util", cll=1)
        # cmds.rowLayout(nc=2)
        cmds.button('Open Selection AR', c=self.onOpenARClicked)
        cmds.button('Back To Last Level', c=self.onBackLevelClicked)
        cmds.button('Add Anim-Trigger', c=NAGA.createTriggerNode)
        cmds.button('Add Proxy', c=NAGA.createProxyNode)
        cmds.button('Add Script', c=NAGA.createScriptNode)
        cmds.button('Add Anim Rig', c=self.onCreateRigButtonClicked)
        cmds.button('Add Movement', c=NAGA.createMovementNode)
        for i in [0, 7]:
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
        #
        self.updateUIByData()

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

    def onCreateRigButtonClicked(self, *arg):
        NAGA.createAnimRigNode(self.naga.getRigList())

    def updateUIByData(self):
        #
        displayName = '*** %s ***' % NAGA.getSceneName()
        cmds.text(self.nameText, e=1, label=displayName)
        #
        last_hko = NAGA.readHistory('last_hko_type')
        last_rig = NAGA.readHistory('last_rig_type')
        last_package = NAGA.readHistory('last_package_type')
        print('last_hko=%d' % last_hko)
        print('last_rig=%d' % last_rig)
        print('last_package=%d' % last_package)
        cmds.optionMenuGrp(self.hkoTypeGroup, e=1, sl=last_hko)
        cmds.optionMenuGrp(self.rigTypeGroup, e=1, sl=last_rig)
        cmds.optionMenuGrp(self.packageGroup, e=1, sl=last_package)

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
        self.naga.convertHkx(exportName, packageName, bDebug=DEBUG)

    def export(self, exportName):

        #
        packageIndex = cmds.optionMenuGrp(self.packageGroup, q=1, sl=1) - 1
        packageName = self.naga.getPackageList()[packageIndex]
        packageName = packageName
        NAGA.updateHistoryNode('last_package_type', packageIndex + 1)

        #
        rigIndex = cmds.optionMenuGrp(self.rigTypeGroup, q=1, sl=1) - 1
        rigName = self.naga.getRigList()[rigIndex]
        rigName = os.path.basename(rigName)
        NAGA.updateHistoryNode('last_rig_type', rigIndex + 1)

        #
        hkoIndex = cmds.optionMenuGrp(self.hkoTypeGroup, q=1, sl=1) - 1
        NAGA.updateHistoryNode('last_hko_type', hkoIndex + 1)

        #
        self.doExport(exportName,
                      packageName,
                      hkoType=hkoIndex,
                      rigName=rigName)


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
