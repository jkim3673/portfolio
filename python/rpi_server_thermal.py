import os
import datetime
import numpy as np
import cv2
import sys
import socket
import select
import queue
import pickle
import struct
import time
from threading import Thread

class WebcamVideoStream:
    def __init__(self, src=0):
        self.stream = cv2.VideoCapture(src)
        cv2.VideoWriter_fourcc('M','J','P','G')
        self.stream .set(cv2.CAP_PROP_BUFFERSIZE,1)
        self.stream .set(5, 60)
        self.stream .set(3,640)
        self.stream .set(4,480)
        (self.grabbed, self.frame) = self.stream.read()
        self.stopped = False

    def start(self):
        Thread(target=self.update, args=()).start()
        return self
    def update(self):
        while True:
            if self.stopped:
                return
            (self.grabbed, self.frame) = self.stream.read()
            time.sleep(0.1)
    def read(self):
        img= cv2.cvtColor(self.frame , cv2.COLOR_BGR2GRAY)
        data = pickle.dumps(img)
        return data
    def stop(self):
        self.stopped = True


def commandParser(cmd, stream):
    reply = ""
    if(cmd == "getimage"):
        reply = stream.read()
        time.sleep(0.1)
    else:
        reply = '/n'.encode()
    return(reply)

if __name__ == '__main__':
    camera_idx = 0
    for i in range(3):
        stream = cv2.VideoCapture(i)
        test,frame = stream.read()
        stream.release()
        if test == True:
            camera_idx = i
            break
    #stream = cv2.VideoCapture(camera_idx)
    vs = WebcamVideoStream(src=camera_idx).start()

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    port = 8080
    server.bind(('192.168.128.14', port))
    server.listen(5)
    inputs = [server]
    outputs = []
    message_queues = {}
    cmd =""
    while inputs:
        readable, writable, exceptional = select.select(inputs, outputs, inputs, 1)
        for s in readable:
            if s is server:
                connection, client_address = s.accept()
                inputs.append(connection)
                message_queues[connection] = queue.Queue(1024)
            else:
                data = s.recv(4096)
                if data:
                    cmd = data.decode()
                    message_queues[s].put(commandParser(data.decode(), vs))
                    if s not in outputs:
                                    outputs.append(s)
                else:
                    if s in outputs:
                        outputs.remove(s)
                    inputs.remove(s)
                    s.close()
                    del message_queues[s]

        for s in writable:
            try:
                next_msg = message_queues[s].get_nowait()
            except queue.Empty:
                outputs.remove(s)

            else:
                if(cmd == "getimage"):
                    size = len(next_msg)
                    s.sendall(struct.pack(">L", size) + next_msg)
                else:
                    s.send("ABCDEFGHIJKLMNONOOO".encode())


        for s in exceptional:
            print ('handling exceptional condition for', s.getpeername())
            inputs.remove(s)
            if s in outputs:
                outputs.remove(s)
            s.close()
            del message_queues[s]
    vs.stop() 