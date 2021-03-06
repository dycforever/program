#!/bin/sh

# 1s means use one static.cc 
g++ -g -c -fPIC static.cc -o static.o
g++ -g -c -fPIC static2.cc -o static2.o

g++ -g -c -fPIC dylib_test1.cc -o dylib_test1.o
g++ -shared -o libtest1.so dylib_test1.o static.o

g++ -g -c -fPIC dylib_test2.cc -o dylib_test2.o
g++ -shared -o libtest2.so dylib_test2.o static.o

g++ -g static_link_app.cc -L./ -ltest1 -ltest2

LD_LIBRARY_PATH=./ ./a.out