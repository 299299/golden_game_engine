#!/bin/env python

import sys
import subprocess
import os
import time

mayaPath_posix = '/usr/autodesk/maya/bin/mayapy'
scriptPath_posix = '/home/lixin/maya/2014-x64/scripts/MayaBatchExport.py'

mayaPath_windows = 'c:/program files/autodesk/maya2014/bin/mayapy.exe'
scriptPath_windows = 'c:/users/Administrator/documents/maya/\
                     scripts/MayaBatchExport.py'


def main(argv):
    folder = argv[1]
    package = argv[2]
    print('folder = ' + folder)
    print('package = ' + package)
    timeStart = time.clock()
    isPosix = os.name == 'posix'
    if isPosix:
        mayaPath = mayaPath_posix
        scriptPath = scriptPath_posix
    else:
        mayaPath = mayaPath_windows
        scriptPath = scriptPath_windows

    args = [mayaPath, scriptPath, folder, package]
    print(args)
    maya = subprocess.Popen(
        args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    while True:
        line = maya.stdout.readline()
        if len(line) > 3:
            print(line)
        if line == '':
            break
    timeEnd = time.clock()
    print('BATCH TOTAL TIME COST [%s] SECONDS!' % str(timeEnd - timeStart))
    # time.sleep(5.0)

if __name__ == '__main__':
    main(sys.argv)
