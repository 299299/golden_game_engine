# -- coding: utf-8 --
import websocket
import threading


def setWebTrace(flag):
    websocket.enableTrace(flag)


class MayaWebSocket(object):

    """docstring for ClassName"""

    def __init__(self):
        self.ws = None
        self.socketThread = None
        self.openCallback = None
        self.closed = True
        self.queueLock = threading.Lock()
        self.workList = []

    def connect(self, callback=None):
        self.disconnect()
        self.ws = websocket.WebSocketApp("ws://localhost:6161",
                                         on_open=self.__on_open,
                                         on_message=self.__on_message,
                                         on_error=self.__on_error,
                                         on_close=self.__on_close)
        self.openCallback = callback
        self.socketThread = threading.Thread(target=self.__run, args=())
        self.socketThread.start()

    def disconnect(self):
        if(self.ws):
            self.ws.close()
        self.join()
        self.ws = None
        self.workList = []

    def join(self):
        if(self.socketThread):
            self.socketThread.join()
    #
    #   WEBSOCKET CALLBACKS
    #

    def __on_message(self, ws, message):
        self.__loopQueue()
        pass

    def __on_error(self, ws, error):
        print("web socket on error = " + str(error) + "\n")

    def __on_close(self, ws):
        print("### closed ###")
        self.ws = None
        self.closed = True

    def __on_open(self, ws):
        self.sendProfing()
        if(self.openCallback):
            self.openCallback()
        self.closed = False

    #
    #   WEBSOCKET FUNCTIONS
    #
    def __run(self, *args):
        print("======thread start=======\n")
        self.ws.run_forever()
        print("======thread end=======\n")

    def sendstring(self, stringmsg):
        stringLen = len(stringmsg)
        data0 = stringLen % 256
        data1 = stringLen / 256
        sendOutString = '%s%s%s' % (chr(data0), chr(data1), stringmsg)
        #print("send out " + sendOutString + "\n")
        self.ws.send(sendOutString, websocket.ABNF.OPCODE_BINARY)

    def sendmayacommand(self, commandName, data):
        msg = '{"command":"%s", "data":"%s", "type":"maya.command"}' % (
            commandName, data)
        self.__putDataToWorkQueue(msg)

    def sendProfing(self):
        self.sendstring('{"type":"application.service.sendProfiling"}')

    def __putDataToWorkQueue(self, data):
        self.queueLock.acquire()
        self.workList.append(data)
        self.queueLock.release()

    def __getDataFromWorkQueue(self):
        dataToReturn = ''
        self.queueLock.acquire()
        listLen = len(self.workList)
        if listLen != 0:
            dataToReturn = self.workList.pop(0)
        self.queueLock.release()
        return dataToReturn

    def __loopQueue(self):
        data = self.__getDataFromWorkQueue()
        if(data):
            self.sendstring(data)
