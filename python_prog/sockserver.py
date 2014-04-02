#!/usr/bin/python

import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

address = ("127.0.0.1", 8715)
sock.bind(address)

backlog = 5
sock.listen(backlog)

while True:
    connection,address = sock.accept()
    try:
        connection.settimeout(5)
        buf = connection.recv(1024)
        print 'buf: %s' % str(buf)
        connection.send('welcome to server!')
    except socket.timeout:
        print 'time out'
    connection.close()
    break
