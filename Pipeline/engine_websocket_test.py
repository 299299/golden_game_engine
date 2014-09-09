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
        arg1 = ord(buf[offset + 1]) * 256
        texLen = arg0 + arg1
        texStart = offset + 2
        real_msg = buf[texStart:texStart + texLen]
        # print real_msg
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
        arg1 = ord(buf[offset + 1]) * 256
        texLen = arg0 + arg1
        texStart = offset + 2
        real_msg = buf[texStart:texStart + texLen]
        # print real_msg
        offset = texStart + texLen
        str_array.append(real_msg)
    return str_array


def string_to_buffer(string):
    strLen = len(string)
    # print 'send len = %d' % strLen
    arr = array.array('B')
    arr.append(strLen % 256)
    arr.append(strLen / 256)
    for char in string:
        arr.append(ord(char))
    return arr


def sendstring(ws, msg):
    ws.send(string_to_buffer(msg), websocket.ABNF.OPCODE_BINARY)


def send_remote_cmd(ws, commandName, data1='', data2=''):
    msg = '{"command":"%s", "data1":"%s", "data2":"%s", \
          "type":"remote.command"}' % (commandName, data1, data2)
    sendstring(ws, msg)


def on_message(ws, data):
    # print(data)
    object_array = buffer_to_json_objects(data)
    for json_object in object_array:
        typeName = json_object['type']
        if(typeName == 'logging.msg'):
            print('[ENGINE LOG] ' + json_object['msg'])


def on_error(ws, error):
    print(error)


def on_close(ws):
    print("### closed ###")


def on_open(ws):
    print("### open!! ###")

    def run(ws):
        while True:
            userInput = raw_input('\n\n please input your command: \n\n')
            if(userInput == ''):
                continue
            commands = userInput.split(',')
            cmdLen = len(commands)
            if cmdLen > 2:
                send_remote_cmd(ws, commands[0], commands[1], commands[2])
            elif cmdLen > 1:
                send_remote_cmd(ws, commands[0], commands[1])
            else:
                send_remote_cmd(ws, commands[0])

    thread.start_new_thread(run, (ws,))


if __name__ == "__main__":
    websocket.enableTrace(True)
    WS = websocket.WebSocketApp("ws://172.26.190.93:6161",
                                on_message=on_message,
                                on_error=on_error,
                                on_close=on_close)
    WS.on_open = on_open
    WS.run_forever()
