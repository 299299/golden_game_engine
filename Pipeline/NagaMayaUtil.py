import os
import shutil
import maya.cmds as cmds
import maya.mel as mel
import maya.api.OpenMaya as OpenMaya
import time
import subprocess
import math
import getpass

PROXY_PREFIX = 'Proxy_'
PROXY_GROUP = 'Proxy'


def getMatrix(node):
    selection = OpenMaya.MSelectionList()
    matrixObject = OpenMaya.MObject()
    selection.add(node)
    MObjectA = selection.getDependNode(0)
    fnThisNode = OpenMaya.MFnDependencyNode(MObjectA)
    worldMatrixAttr = fnThisNode.attribute("worldMatrix")
    matrixPlug = OpenMaya.MPlug(MObjectA, worldMatrixAttr)
    matrixPlug = matrixPlug.elementByLogicalIndex(0)
    matrixObject = matrixPlug.asMObject()
    worldMatrixData = OpenMaya.MFnMatrixData(matrixObject)
    worldMatrix = worldMatrixData.matrix()
    return worldMatrix


def decompMatrix(node, matrix):
    rotOrder = cmds.getAttr('%s.rotateOrder' % node)
    mTransformMtx = OpenMaya.MTransformationMatrix(matrix)
    trans = mTransformMtx.translation(OpenMaya.MSpace.kWorld)
    eulerRot = mTransformMtx.rotation()
    eulerRot.reorderIt(rotOrder)
    angles = [math.degrees(angle)
              for angle in (eulerRot.x, eulerRot.y, eulerRot.z)]
    scale = mTransformMtx.scale(OpenMaya.MSpace.kWorld)
    return [trans.x, trans.y, trans.z], angles, scale


def syncWorldMatrix(in_node, out_node):
    mat = getMatrix(in_node)
    matDecomp = decompMatrix(in_node, mat)
    translate = matDecomp[0]
    rotate = matDecomp[1]
    scale = matDecomp[2]
    cmds.setAttr(out_node + '.translate',
                 translate[0], translate[1], translate[2])
    cmds.setAttr(out_node + '.rotate', rotate[0], rotate[1], rotate[2])
    cmds.setAttr(out_node + '.scale', scale[0], scale[1], scale[2])


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


def isLevel(name):
    return name.startswith('Level')
    # return len(findNodeNamePrefix('Proxy')) > 0


def fixAssemblyRepPath():
    nodeList = cmds.ls(type='assemblyDefinition')
    for node in nodeList:
        dataAttrib = node + '.representations[0].repData'
        data = cmds.getAttr(dataAttrib)
        # FIXME just hack with c:/ start or d:/ start
        if data.startswith('C:/') or data.startswith('D:/'):
            pos = data.find('/LevelData') + 1
            strlen = len(data)
            data = data[pos: strlen]
            print(data)
            cmds.setAttr(dataAttrib, data, type='string')


def getNoneCameraNode():
    nodeList = cmds.ls(type='transform')
    for node in nodeList:
        if(node == 'front' or node == 'persp' or
           node == 'side' or node == 'top'):
            continue
        return node
    return ''


def isJointNodeExist():
    nodeList = cmds.ls(type='joint')
    return len(nodeList) > 0


def fixAssemblyTransform():
    node = getNoneCameraNode()
    if(node == ''):
        return
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


def findNodeNamePrefix(prefix):
    nodeList = cmds.ls(type='transform')
    retList = []
    for node in nodeList:
        if(node.startswith(prefix)):
            retList.append(node)
    return retList


def findNodeNameEqual(name):
    nodeList = cmds.ls(type='transform')
    for node in nodeList:
        if(node == name):
            return node
    return ''


def getMayaScriptPath():
    userName = getpass.getuser()
    return 'C:/Users/%s/Documents/maya/scripts/' % (userName)


def addBackSlash(str):
    strLen = len(str)
    if str[strLen - 1] != '/':
        return str + '/'
    return str


def addFloatAttr(node_name, attr_name, float_value=None):
    cmds.addAttr(node_name, ln=attr_name)
    if(float_value):
        cmds.setAttr(node_name + '.' + attr_name, float_value)


def addStringAttr(node_name, attr_name, string_value=None):
    cmds.addAttr(node_name, ln=attr_name, dt='string')
    if(string_value):
        cmds.setAttr(node_name + '.' + attr_name, string_value, type='string')


def addFloat3Attr(node_name, attr_name, float3_values=None):
    cmds.addAttr(node_name, ln=attr_name, at='float3')
    cmds.addAttr(node_name, at='float', ln=attr_name + 'X', parent=attr_name)
    cmds.addAttr(node_name, at='float', ln=attr_name + 'Y', parent=attr_name)
    cmds.addAttr(node_name, at='float', ln=attr_name + 'Z', parent=attr_name)
    if(float3_values):
        cmds.setAttr(node_name + '.' + attr_name, float3_values[0],
                     float3_values[1], float3_values[2], type='float3')


def addEnumAttr(node_name, attr_name, enum_values):
    enum_names = ''
    for enum_name in enum_values:
        enum_names += enum_name
        enum_names += ':'
    cmds.addAttr(node_name, ln=attr_name, at='enum', en=enum_names)


def createProxyNode():
    proxy_node_name = 'proxy'
    proxy_node = findNodeNameEqual(proxy_node_name)
    if(proxy_node != ''):
        return
    proxy_node = cmds.group(em=1, name=proxy_node_name)
    addStringAttr(proxy_node, 'hkType', 'engine_attributes')
    addFloat3Attr(proxy_node, 'gravity', [0, -9.8, 0])
    addFloatAttr(proxy_node, 'radius', 0.5)
    addFloatAttr(proxy_node, 'stand_height', 2.0)
    addFloatAttr(proxy_node, 'friction', 0.9)
    addFloatAttr(proxy_node, 'strength', 1.0)
    addFloatAttr(proxy_node, 'vertical_gain', 0.2)
    addFloatAttr(proxy_node, 'horizontal_gain', 0.8)
    addFloatAttr(proxy_node, 'max_vertical_separation', 5.0)
    addFloatAttr(proxy_node, 'max_horizontal_separation', 0.15)
    addFloatAttr(proxy_node, 'offset', 1.0)
    addStringAttr(proxy_node, 'collision_layer', 'character_proxy')


def createTriggerNode():
    triggers = ['attack', 'dust']
    TRIGGER_GROUP = 'triggers'
    trigger_group = findNodeNameEqual(TRIGGER_GROUP)
    if(trigger_group == ''):
        addEnumAttr(trigger_group, 'hk_trigger_', triggers)

    BEAT_GROUP = 'beats'
    beat_group = findNodeNameEqual(BEAT_GROUP)
    if(beat_group == ''):
        beat_group = cmds.group(em=1, name=BEAT_GROUP)
        addEnumAttr(
            beat_group, 'hk_beat_', ['left_foot_down', 'right_foot_down'])


class NagaMayaUtil(object):

    def __init__(self):
        nagaKey = 'NAGA_DIR'
        self.linuxVersion = False
        if nagaKey in os.environ:
            nagaDir = os.environ['NAGA_DIR']
        else:
            nagaDir = os.environ['HOME'] + '/work/GameProject/'
            self.linuxVersion = True
        if not self.linuxVersion:
            cmds.loadPlugin("hctMayaSceneExport")
        nagaDir = nagaDir.replace("\\", "/")
        self.mayaFiles = dict()
        self.onNagaPathChanged(nagaDir)

    def onNagaPathChanged(self, nagaDir):
        print('\n####### naga path changed = %s ########\n' % (nagaDir))
        nagaDir = os.path.join(nagaDir, '')
        nagaDir = nagaDir.replace('\\', '/')
        self.nagaPath = nagaDir
        self.pipelinePath = nagaDir + 'Pipeline/'
        self.hkoPath = self.pipelinePath + 'havok_hko/'
        self.appPath = nagaDir + 'Application/'
        self.intermediatePath = self.appPath + 'intermediate/'
        self.mayaDataBaseFile = self.appPath + 'maya_export_database.txt'
        self.readMayaDatabase(self.mayaDataBaseFile)

    def getHkxFolder(self, packageName):
        return self.nagaPath + 'DCC_Export/Havok/' + packageName + '/'

    def getLevelFile(self, packageName):
        levelOut = self.intermediatePath + packageName + '/'
        levelOut += packageName
        levelOut += '.level'
        return levelOut

    def getPackageFolder(self):
        nodeList = cmds.ls(type='assemblyDefinition')
        if(len(nodeList) == 0):
            return ''
        node = nodeList[0]
        entityType = getAD_EntityType(node)
        root = self.nagaPath + 'DCC_Export/Havok/'
        dirs = os.listdir(root)
        for dirName in dirs:
            dirName = os.path.join(root, dirName)
            fileName = dirName + '/' + entityType + '.hkx'
            print(fileName)
            if(os.path.exists(fileName)):
                return dirName
        return ''

    def addLevelProxy(self):
        packageFolderName = self.getPackageFolder()
        if packageFolderName == '':
            cmds.warning('packageFolderName not find.')
            return -1
        proxyNodeNum = 0
        packageName = ''
        group = findNodeNameEqual(PROXY_GROUP)
        if(group != ''):
            cmds.delete(PROXY_GROUP)
        group = PROXY_GROUP
        packageName = os.path.basename(packageFolderName)
        hkxFolder = self.getHkxFolder(packageName)
        print('havok export folder = ' + hkxFolder)
        group = cmds.group(em=1, name=PROXY_GROUP)
        addStringAttr(group, 'hkType', 'engine_attributes')
        addStringAttr(group, 'package_name', packageName)

        nodeList = cmds.ls(type='assemblyDefinition')

        for ad_node in nodeList:
            mesh_node = cmds.listRelatives(ad_node, c=1, f=1)[0]
            print('ad node = ' + ad_node)
            print('mesh node = ' + mesh_node)
            proxyNodeName = PROXY_PREFIX + ad_node
            entityType = getAD_EntityType(ad_node)
            havokFileName = os.path.join(hkxFolder, entityType + '.hkx')
            if(not os.path.exists(havokFileName)):
                cmds.warning('havok file not exist -->' + havokFileName)
                continue
            nodeName = cmds.createNode('transform', n=proxyNodeName, p=group)
            resourceName = packageName + '/actor/' + entityType
            # add custom attributes for serialize
            addStringAttr(nodeName, 'hkType', 'engine_attributes')
            addStringAttr(nodeName, 'name', ad_node)
            addStringAttr(nodeName, 'type', resourceName)
            addStringAttr(nodeName, 'line_node', ad_node)
            #syncWorldMatrix(mesh_node, nodeName)
            cmds.copyAttr(mesh_node, nodeName, ic=0, oc=0, v=1)
            proxyNodeNum += 1
        # cmds.delete(PROXY_GROUP)
        return proxyNodeNum, packageName

    def exportToHKX(self, exportName, packageName,
                    hko_index, rig='', arg='', s=False):

        hkoFullPath = self.getHkoList()[hko_index]
        outputPath = self.getHkxFolder(packageName)
        if not os.path.exists(outputPath):
            os.makedirs(outputPath)
        ouputFileName = outputPath + exportName + '.hkx'

        eval_cmd = 'hkCmdExportScene -o \"' + hkoFullPath + '\" -b -v '
        if s:
            eval_cmd += "-s "
        eval_cmd += "-ev "
        envCmd = "HK_OUTPUT=" + ouputFileName + ";"
        workSpace = cmds.workspace(q=True, dir=True, rd=True)
        envCmd += "WORK_SPACE=" + workSpace + ";"
        exportMode = "model"
        if(isLevel(exportName)):
            exportMode = "level"
        elif(hkoFullPath.find('skin_model') != -1):
            exportMode = 'skinning'
        elif(hkoFullPath.find('animation') != -1):
            exportMode = 'animation'
        envCmd += "EXPORT_MODE=" + exportMode + ";"

        if(rig):
            rigFile = self.pipelinePath + rig
            # can not set full rig path to env
            # I`m not sure why
            #envCmd += "RIG_FILE=" + rigFile + ";"
            #envCmd += "RIG_FILE=output_rig.txt;"
            envCmd += "SK_NAME=" + exportName + ";"
            sceneDir = getSceneDirectory()
            print("scene dir = " + sceneDir)
            tmpRigFile = sceneDir + "\\output_rig.txt"
            rigFile = self.pipelinePath + 'bones/' + rig
            print('rig file = ' + rigFile)
            shutil.copyfile(rigFile, tmpRigFile)

        if(arg):
            envCmd += arg
        eval_cmd += '"' + envCmd + '"'

        print(eval_cmd)
        mel.eval(eval_cmd)

        # if(rig):
        #    shutil.rmFile(tmpRigFile)

    def convertHkx(self, exportName, packageName, bCompile=True, bDebug=False):
        convertOutputDir = 'intermediate/' + packageName + '/'
        arg0 = '-f'
        arg1 = self.getHkxFolder(packageName) + exportName + '.hkx'
        arg2 = '-o'
        arg3 = convertOutputDir
        args = [arg0, arg1, arg2, arg3]
        if(bDebug):
            args.append('--debug')
        print('HavokConvert ' + str(args))
        lunchApplication(
            'HavokConverter.exe', self.appPath, args, True)
        if bCompile:
            arg0 = '-i'
            arg1 = convertOutputDir
            args = [arg0, arg1]
            print('DataCompiler ' + str(args))
            lunchApplication(
                'DataCompiler.exe', self.appPath, args, True)

    def getPackageList(self):
        folderList = os.listdir(self.intermediatePath)
        retList = []
        for folder in folderList:
            if folder != 'core':
                retList.append(folder)
        return retList

    def getRigList(self):
        return osGetFileList(self.pipelinePath + 'bones', '.bones')

    def getHkoList(self):
        return osGetFileList(self.pipelinePath + 'hko', '.hko')

    #
    #
    # API FOR BATCH
    #
    #

    def batchExport(self, folder, packageName):
        time1 = time.clock()
        mayaFileList = osGetFileList(folder, 'mb')
        if len(mayaFileList) == 0:
            cmds.warning('not maya files in this folder!')
            return
        outputFolder = self.getHkxFolder(packageName)
        if not os.path.exists(outputFolder):
            print('mkdirs ' + outputFolder)
            os.makedirs(outputFolder)
        numBatchExport = 0
        print('file list num = %d' % len(mayaFileList))
        for mayaFile in mayaFileList:
            base = os.path.basename(mayaFile)
            name, ext = os.path.splitext(base)
            if base.startswith('AD_'):
                continue
            print('processing file ' + mayaFile)
            ouputFileName = outputFolder + name + '.hkx'
            if os.path.exists(ouputFileName):
                if not self.isFileChanged(mayaFile):
                    print(mayaFile + ' not changed')
                    continue
            numBatchExport += 1
            print('openning file ' + mayaFile)
            cmds.file(mayaFile, force=True, open=True)
            self.exportToHKX(name, packageName, 0)
            cmds.file(mf=0)
            print('end openning file ' + mayaFile)
            self.updateFileInfo(mayaFile)
            self.saveMayaDatabase(self.mayaDataBaseFile)

        timeDiff = time.clock() - time1
        print('%d file exported, time cost = %s seconds.' %
              (numBatchExport, str(timeDiff)))
        return timeDiff

    def readMayaDatabase(self, fileName):
        if not os.path.exists(fileName):
            return
        self.mayaFiles.clear()
        f = open(fileName, 'r')
        lines = f.readlines()
        for line in lines:
            line = line.strip('\n')
            nameList = line.split(',')
            key = nameList[1]
            value = nameList[0]
            line = '%s,%s' % (value, key)
            self.mayaFiles[key] = value

    def saveMayaDatabase(self, fileName):
        f = open(fileName, 'w')
        for key, value in self.mayaFiles.items():
            line = '%s,%s\n' % (value, key)
            f.write(line)
        f.close()

    def isFileChanged(self, fileName):
        if not os.path.exists(fileName):
            print('file not exit')
            return True
        if fileName not in self.mayaFiles:
            print('file not in database')
            return True
        mtime = os.path.getmtime(fileName)
        mtimeStr = str(mtime)
        if self.mayaFiles[fileName] != mtimeStr:
            print('file changed ' + mtimeStr)
            return True
        return False

    def updateFileInfo(self, fileName):
        mtime = os.path.getmtime(fileName)
        newValue = str(mtime)
        if(fileName in self.mayaFiles):
            dct = {fileName: newValue}
            self.mayaFiles.update(dct)
        else:
            self.mayaFiles[fileName] = newValue


def batch_export(folder, package):
    import maya.standalone as std
    std.initialize(name='python')
    f = NagaMayaUtil()
    f.batchExport(folder, package)
