# -- coding: utf-8 --
import websocket
reload(websocket)
import threading
import time
import array
import json


def setWebTrace(flag):
    websocket.enableTrace(flag)


def string_to_buffer(string):
    strLen = len(string)
    # print 'send len = %d' % strLen
    arr = array.array('B')
    arr.append(strLen % 256)
    arr.append(strLen / 256)
    for char in string:
        arr.append(ord(char))
    return arr


def buffer_to_json_objects(buf):
    dataLen = len(buf)
    offset = 0
    object_array = []
    while offset < dataLen:
        arg0 = ord(buf[offset])
        arg1 = ord(buf[offset + 1]) * 256
        texLen = arg0 + arg1
        texStart = offset + 2
        texLeft = dataLen - offset - 2
        if texLen > texLeft:
            texLen = texLeft
        msg_bytes = buf[texStart:texStart + texLen]
        #str_msg = msg_bytes.encode('utf-8')
        offset = texStart + texLen
        json_object = json.loads(msg_bytes)
        object_array.append(json_object)
    return object_array


class MayaWebSocket(object):

    def __init__(self):
        self.ws = None
        self.socketThread = None
        self.openCallback = None
        self.onMessageCallback = None
        self.onClosedCallback = None
        self.closing = False
        self.connected = False
        self.queueLock = threading.Lock()
        self.workList = []

    def connect(self, callback1=None, callback2=None, callback3=None):
        self.disconnect()
        self.closing = False
        self.ws = websocket.WebSocketApp("ws://localhost:6161",
                                         on_open=self.__on_open,
                                         on_message=self.__on_message,
                                         on_error=self.__on_error,
                                         on_close=self.__on_close)
        self.openCallback = callback1
        self.onMessageCallback = callback2
        self.onClosedCallback = callback3
        self.socketThread = threading.Thread(target=self.__run, args=())
        self.socketThread.start()

    def disconnect(self):
        self.closing = True
        if self.ws:
            self.ws.close()
        if self.socketThread:
            print('wait for socket thread exit')
            # self.socketThread.join()
            print('wait for socket thread finished')
        self.ws = None
        self.workList = []

    #
    #   WEBSOCKET CALLBACKS
    #

    def __on_message(self, ws, data):
        if self.onMessageCallback:
            object_array = buffer_to_json_objects(data)
            for json_object in object_array:
                self.onMessageCallback(json_object)
        self.__loopQueue()

    def __on_error(self, ws, error):
        self.workList = []
        #print('----> web socket on error = ' + str(error))

    def __on_close(self, ws):
        # print('################ web socket on close ################')
        self.connected = False
        self.workList = []

    def __on_open(self, ws):
        # print('################web socket on open################')
        self.connected = True
        self.workList = []
        if(self.openCallback):
            self.openCallback()

    #
    #   WEBSOCKET FUNCTIONS
    #
    def __run(self, *args):
        while not self.closing:
            #print('ws run_forever start')
            self.ws.run_forever()
            #print('ws run_forever end')
            if self.closing:
                return
            for i in range(0, 5):
                if self.closing:
                    return
                time.sleep(0.5)

    def sendstring(self, stringmsg):
        self.ws.send(string_to_buffer(stringmsg),
                     websocket.ABNF.OPCODE_BINARY)

    def sendmayacommand(self, commandName, data1='', data2=''):
        msg = '{"command":"%s", "data1":"%s", "data2":"%s", "type":"remote.command"}'\
            % (commandName, data1, data2)
        print(msg)
        self.__putDataToWorkQueue(msg)

    def __putDataToWorkQueue(self, data):
        self.queueLock.acquire()
        self.workList.append(data)
        self.queueLock.release()

    def __getDataFromWorkQueue(self):
        dataToReturn = ''
        self.queueLock.acquire()
        listLen = len(self.workList)
        if listLen:
            dataToReturn = self.workList.pop(0)
        self.queueLock.release()
        return dataToReturn

    def __loopQueue(self):
        data = self.__getDataFromWorkQueue()
        if(data):
            self.sendstring(data)
