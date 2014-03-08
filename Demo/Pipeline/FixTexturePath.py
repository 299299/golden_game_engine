import maya.cmds as cmds
import os


class FixTexturePath(object):

    def __init__(self):
        self.newName = ''
        self.createUI()

    def createUI(self):
        if cmds.window('FIX_TEXTURE_UI', exists=True):
            cmds.deleteUI('FIX_TEXTURE_UI')
        win = cmds.window(
            'FIX_TEXTURE_UI', title="RV TEXTURE PATH FIX", w=350, h=150)
        cmds.columnLayout(adjustableColumn=True)
        cmds.text(
            "FIRST > select your file nodes in Hypershade!!", bgc=(1, 0, 0))
        cmds.frameLayout(l="browse folder for textures")
        cmds.flowLayout()
        cmds.text("file Path", h=25)
        self.pathText = cmds.textField(w=250, h=25)
        self.loadBtn = cmds.button(
            w=50, h=25, label="get", c=self.selectDir)

        cmds.setParent('..')
        self.fixit = cmds.button(
            l="Fix textures", c=self.renameTex)
        cmds.setParent('..')
        cmds.showWindow(win)

    def renameTex(self, *arg):
        if not self.newName:
            return

        tex = cmds.ls(sl=True, type="file")
        for item in tex:

            fullpath = cmds.getAttr("%s.fileTextureName" % item)
            fileName = fullpath.split("/")[-1]
            newPath = os.path.join(self.newName, fileName)
            cmds.setAttr("%s.fileTextureName" %
                         item, newPath, type="string")

    def selectDir(self, *arg):
        folder = cmds.fileDialog2(cap="locate folder", fm=3)
        if not folder:
            return
        uniToStr = str(folder)

        filePath = uniToStr.split("'")[1]
        cmds.textField(self.pathText, edit=True, text=filePath)
        self.newName = filePath
