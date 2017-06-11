#!/usr/bin/python

import struct
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#host = socket.gethostname()
host = '192.168.112.251'
port = 666

s.connect((host, port))

action   = socket.ntohs(2)
peer_id  = socket.ntohl(1234) 
action   = struct.pack('h', action)
peer_id  = struct.pack('I', peer_id)


while True:
    msgbody     = input('say sth: ')
    msgbody_len = len(msgbody)

    msgbody_len  = socket.ntohs(msgbody_len) 
    msgbody_len  = struct.pack('h', msgbody_len)

    send_msg = action + peer_id + msgbody_len + msgbody.encode('utf-8')
    s.send(send_msg)

    msg = s.recv(1024)
    print(msg.decode('utf-8'))
