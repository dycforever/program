#!/bin/sh

# 2s means use two static.cc 
g++ -c -fPIC static.cc -o static.o
g++ -c -fPIC static2.cc -o static2.o

g++ -c -fPIC dylib_test1.cc -o dylib_test1.o
g++ -shared -o libtest1.so dylib_test1.o static.o

g++ -c -fPIC -DHELLO2 dylib_test2.cc -o dylib_test2.o
g++ -shared -o libtest2.so dylib_test2.o static2.o

g++ -g static_link_app.cc -L./ -ltest1 -ltest2

LD_LIBRARY_PATH=./ ./a.out