#!/usr/bin/python

import struct
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#host = socket.gethostname()
host = '127.0.0.1'
port = 666

s.connect((host, port))

login = socket.ntohs(1)
login = struct.pack('h',login)
action   = socket.ntohs(2)
peer_id  = socket.ntohl(632949210)
myid = 632949210
action   = struct.pack('h', action)
peer_id  = struct.pack('I', peer_id)
myid = struct.pack('I',myid)



msgbody_len = 4
msgbody_len  = socket.ntohs(msgbody_len)
msgbody_len  = struct.pack('h', msgbody_len)
send_login = login + peer_id + msgbody_len + myid
s.send(send_login)


while True:
    msgbody     = input('say sth: ')
    msgbody_len = len(msgbody)

    msgbody_len  = socket.ntohs(msgbody_len)
    msgbody_len  = struct.pack('h', msgbody_len)

    send_msg = action + peer_id + msgbody_len + msgbody.encode('utf-8')
    s.send(send_msg)

    msg = s.recv(1024)
    print(msg.decode('utf-8'))
