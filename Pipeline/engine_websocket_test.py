import websocket
import thread
import time
import array
import json


def buffer_to_json_objects(buf):
    dataLen = len(buf)
    offset = 0
    object_array = []
    while offset < dataLen:
        arg0 = ord(buf[offset])
        arg1 = ord(buf[offset+1]) * 256
        texLen = arg0 + arg1
        texStart = offset + 2
        real_msg = buf[texStart:texStart+texLen]
        #print real_msg
        offset = texStart + texLen
        json_object = json.loads(real_msg)
        object_array.append(json_object)
    return object_array

def buffer_to_strings(buf):
    dataLen = len(buf)
    offset = 0
    str_array = []
    while offset < dataLen:
        arg0 = ord(buf[offset])
        arg1 = ord(buf[offset+1]) * 256
        texLen = arg0 + arg1
        texStart = offset + 2
        real_msg = buf[texStart:texStart+texLen]
        #print real_msg
        offset = texStart + texLen
        str_array.append(real_msg)
    return str_array
    
def string_to_buffer(string):
    strLen = len(string)
    #print 'send len = %d' % strLen
    arr = array.array('B')
    arr.append(strLen % 256)
    arr.append(strLen / 256)
    for char in string:
        arr.append(ord(char))
    return arr    
    
def on_message(ws, data):
    #print message
    object_array = buffer_to_json_objects(data)
    for json_object in object_array:
        print(json_object)

def on_error(ws, error):
    print error

def on_close(ws):
    print "### closed ###"

def on_open(ws):
    print "### open!! ###"
    def run(*args):
        for i in range(3):
            time.sleep(1)
            arr = string_to_buffer('{"type":"application.service.quit"}')
            #ws.send(arr, websocket.ABNF.OPCODE_BINARY)
        time.sleep(1)
        #ws.close()
        print "thread terminating..."
    thread.start_new_thread(run, ())


if __name__ == "__main__":
    websocket.enableTrace(True)
    ws = websocket.WebSocketApp("ws://172.26.190.93:6161",
                                on_message = on_message,
                                on_error = on_error,
                                on_close = on_close)
    ws.on_open = on_open

    ws.run_forever()
