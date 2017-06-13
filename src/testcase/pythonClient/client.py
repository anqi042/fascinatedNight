#!/usr/bin/python

import struct
import socket
import threading

#host = socket.gethostname()
host = '192.168.112.251'
port = 666

class myThread(threading.Thread) :
    def __init__(self, func):
        threading.Thread.__init__(self)
        self.func = func

    def run(self):
        self.func()


action   = socket.ntohs(2)
peer_id  = socket.ntohl(632949210)
action   = struct.pack('h', action)
peer_id  = struct.pack('I', peer_id)

class FasyClient(socket.socket):
    def __init__(self, host, port):
        self.host = host
        self.port = port
        socket.socket.__init__(self,
                        socket.AF_INET, 
                        socket.SOCK_STREAM)

    def server_connect(self):
        self.connect((self.host, self.port))
 
    def service_start(self):
        thread_recv = myThread(self.worker_recv)
        thread_send = myThread(self.worker_send)

        thread_recv.start()
        thread_send.start()
        thread_recv.join()
        thread_send.join()
         
    def user_login(self):
        login = socket.ntohs(1)
        login = struct.pack('h',login)
        action   = socket.ntohs(2)
        peer_id  = socket.ntohl(632949210)
        myid = 632949211
        action   = struct.pack('h', action)
        peer_id  = struct.pack('I', peer_id)
        myid = struct.pack('I',myid)

        print ("user login...")
        msgbody_len = 4
        msgbody_len  = socket.ntohs(msgbody_len)
        msgbody_len  = struct.pack('h', msgbody_len)
        send_login = login + peer_id + msgbody_len + myid
        self.send(send_login)

    def worker_recv(self):
        while True:
           msg = self.recv(1024)
           print ('\n'+"receved:"+msg.decode('utf-8')+'\n')
           print ("say sth: ")

    def worker_send(self):
        while True:
           msgbody = input('say sth: ')
           msgbody = msgbody.rstrip()
           msgbody_len = len(msgbody)
           msgbody_len  = socket.ntohs(msgbody_len)
           msgbody_len  = struct.pack('h', msgbody_len)
           send_msg = action + peer_id + msgbody_len + msgbody.encode('utf-8')
           self.send(send_msg)
		
	    
client = FasyClient(host, port)

client.server_connect()

client.user_login()

client.service_start()

print ("exit, bye bye!")

