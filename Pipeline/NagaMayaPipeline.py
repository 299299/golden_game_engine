import os
import maya.cmds as cmds
import maya.mel as mel
import Utils as utils
reload(utils)


UI_NAME = 'Naga_UI'


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
        if not self.nagaDir:
            print('set NAGA_DIR environment first!.')
            cmds.error('!!!!')
        self.nagaDir = self.nagaDir.replace('\\', '/')
        self.binDir = self.nagaDir + 'Application/'
        self.pipelineDir = self.nagaDir + 'Pipeline/'
        self.dataDir = self.binDir + 'Data/'
        self.fbxDir = self.binDir + 'FBX/'
        # create fbx folder if not exist
        if not os.path.exists(self.fbxDir):
            os.makedirs(self.fbxDir)

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
        displayName = '*** %s ***' % utils.getSceneName()
        self.nameText = cmds.text(label=displayName,
                                  align='center',
                                  bgc=[0, 1, 0],
                                  h=30)

        cmds.setParent('..')

        self.exportTypeGrp = cmds.optionMenuGrp('ExportType', l='type:')
        cmds.menuItem(label='model')
        cmds.menuItem(label='scene')
        cmds.menuItem(label='node')
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
        cmds.button('PREVIEW', h=height, bgc=[1, 0, 1],
                    c=self.onPreviewButtonClicked)
        cmds.setParent('..')
        cmds.showWindow(UI_NAME)
        self.updateUIByData()

    def isSelectOnly(self):
        return cmds.checkBox(self.selectCheck, q=1, v=1)

    def onFixPathClicked(self, *arg):
        utils.fixAssemblyRepPath()

    def onOpenARClicked(self, *arg):
        self.lastMayaScene = cmds.file(q=True, sn=True)
        utils.openAD_Reference()

    def onBackLevelClicked(self, *arg):
        if(self.lastMayaScene == ''):
            return
        cmds.file(mf=0)
        cmds.file(self.lastMayaScene, o=True)
        self.lastMayaScene = ''

    def onExportButtonClicked(self, *arg):
        name = utils.getSceneName()
        if name == '':
            return
        self.export(name)

    def onPreviewButtonClicked(self, *arg):
        self.preview()

    def updateUIByData(self):
        #
        name = utils.getSceneName()
        if name == '':
            name = 'untitiled'
        displayName = '*** %s ***' % name
        cmds.text(self.nameText, e=1, label=displayName)

    def getExportType(self):
        return cmds.optionMenuGrp(self.exportTypeGrp, q=1, v=1)

    def export(self, exportName):
        fbxFile = self.fbxDir + exportName + '.fbx'
        presetFile = self.pipelineDir + 'fbx.fbxexportpreset'
        utils.fbx_export(fbxFile, presetFile)
        if not os.path.exists(fbxFile):
            print('export error')
            return
        eType = self.getExportType()
        outputDir = self.dataDir + exportName + '/'
        extName = 'xml'
        if eType == 'model':
            extName = 'mdl'
        outputFile = outputDir + exportName + '.' + extName
        prefixPath = 'Data/' + exportName + '/'
        args = [eType, fbxFile, outputFile, '-t', '-v',
                '-prefix', prefixPath, '-flipuv']
        utils.mkdir(outputDir)
        utils.lunchApplication('NagaTool', self.binDir, args, True)
        self.lastOutputFile = outputFile
        self.lastFBXFile = fbxFile

    def preview(self):
        if not self.lastOutputFile:
            return
        scriptFile = 'Data/Scripts/Viewer.as'
        eType = self.getExportType()
        args = [scriptFile, eType, self.lastOutputFile, '-w']
        utils.lunchApplication('NagaGame', self.binDir, args, False)


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
