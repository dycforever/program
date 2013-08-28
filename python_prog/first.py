#!/usr/bin/python
#edit-mode:-*- python -*-
#coding:utf-8
#str = GLOB('../cpp_prog/*.c*');
#print(str)
#.read()[0:-1];
nint=35
nlong=32
nbool=False
nfloat=0.1
print(nint);
print(nlong);
print(nbool);
print(nfloat);

lin='''haha
zhazha'''
print(lin)
str="g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj."
nstr=""
for c in str:
    if( ord(c) < 123 and ord(c) > 64):
        nstr += chr(ord(c)+2)
    else:
        nstr += c
print("answer:")
print(nstr)
