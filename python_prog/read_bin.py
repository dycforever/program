#!/usr/bin/python

import struct
fp = open("./a.out", "rb")
bytes=fp.read()
if bytes[0]==0x7f:
    print("0:%x" %(bytes[0]))
else:
    print("unknow 0")
    
if bytes[1]==0x45:
    print("1:%x" %(bytes[1]))
else:
    print("unknow %x")
    
