import os
import datetime
import numpy as np
import cv2
import socket
import socket
import sys
import pickle
import struct ## new
import zlib
import time

server_address = ('192.168.128.14', 8080)



s =  socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#print ('connecting to %s port %s' % server_address)
s.connect(server_address)

cv2.namedWindow('Streaming')
payload_size = struct.calcsize(">L")

while True:
    s.send("getimage".encode())

    data = b""
    while len(data) < payload_size:
        data += s.recv(4096)

    packed_msg_size = data[:payload_size]
    data = data[payload_size:]
    msg_size = struct.unpack(">L", packed_msg_size)[0]
    while len(data) < msg_size:
        data += s.recv(4096)
    frame_data = data[:msg_size]
    data = data[msg_size:]
    frame=pickle.loads(frame_data, fix_imports=True, encoding="bytes")
    cv2.imshow('Streaming',frame)
    cv2.waitKey(1)
    #cv2.imwrite("test.tiff", frame)
s.close()