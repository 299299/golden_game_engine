import maya.cmds as cmds

nodeList = cmds.ls(type='assemblyDefinition')
for node in nodeList:
    dataAttrib = node + '.representations[0].repData'
    data = cmds.getAttr(dataAttrib)
    ### FIXME just hack with c:/ start or d:/ start
    if data.startswith('C:/') or data.startswith('D:/'):
        pos = data.find('/LevelData') + 1
        strlen = len(data)
        data = data[pos: strlen]
        print(data)
        cmds.setAttr(dataAttrib, data, type='string')
