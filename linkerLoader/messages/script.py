#!/usr/bin/python3
import sys
print("python path: %s" % (sys.path))
sys.path.append('/home/dyc/tools/python3-protobuf_src/python') 
sys.path.append('.') 
import mesg_pb2

def listBuf(header):
    print("header: %s" % (header.__str__() ))


header = mesg_pb2.HeaderMesg()
f = open("mid.out", "rb")
header.ParseFromString(f.read())
f.close()

listBuf(header)
#
#for i in range(0, header.phnum):
#    phead = mesg_pb2.ProgHeaderMesg()
#    phead.ParseFromString(f.read())
#    print("pheader: %s" % (phead.__str__() ))
#    break

