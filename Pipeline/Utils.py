import os
import maya.cmds as cmds
import maya.mel as mel
import subprocess


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


def getSceneName():
    fileName = cmds.file(q=True, sn=True)
    print("current scene = " + fileName)
    fileName = os.path.basename(fileName)
    if(not fileName):
        cmds.warning('not named scene!')
        return ''
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


def fbx_export(outFile, presetFile):
    print('fbx_export = ' + outFile)
    eval_cmd = 'FBXLoadExportPresetFile -f \"' + presetFile + '\"'
    print(eval_cmd)
    mel.eval(eval_cmd)
    eval_cmd = 'FBXExport -f \"' + outFile + '\"'
    print(eval_cmd)
    mel.eval(eval_cmd)


def mkdir(path):
    path = path.strip()
    path = path.rstrip("\\")
    path = path.rstrip("/")
    isExists = os.path.exists(path)
    if not isExists:
        print(path + ' create success')
        os.makedirs(path)
        return True
    else:
        print(path + ' already exist')
        return False
