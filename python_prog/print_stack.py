#!/usr/bin/python

def func():
    import sys
    frame = sys._getframe()
    print frame.f_locals
    print frame.f_globals
    print frame.f_back.f_locals

def add (a,b):
    func()
    return a+b

sum = add(1,2)
print sum
