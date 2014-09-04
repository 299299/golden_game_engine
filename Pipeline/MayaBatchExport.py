import sys
import maya.standalone as std
std.initialize(name='python')
import NagaMayaUtil as NAGA
reload(NAGA)

folder = sys.argv[1]
package = sys.argv[2]
print('folder = ' + folder)
print('package = ' + package)
NAGA.batch_export(folder, package)
