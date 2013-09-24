
export CPLUS_INCLUDE_PATH=../../common
export CC=g++
#export CFLAGS= -g -pipe -Wall -Werror -fPIC -I./include/ -I../common -L../common
export CFLAGS= -g -pipe -Wall -fPIC -I../include/ -I../../common -L../../common
export CXXFLAGS= -g -pipe -Wall -fPIC -I../include/ -I../../common -L../../common
VPATH=../src

.PHONY:all
all: pingpongServer pingpongClient fileclient fileserver

pingpongServer:Connection.o Client.o Server.o EventLoop.o Epoller.o InetAddress.o Socket.o pingpongServer.cpp Task.o 
	g++ -o $@ $(CFLAGS) $^ -lpthread -lcommon

pingpongClient:Connection.o Client.o Server.o EventLoop.o Epoller.o InetAddress.o Socket.o pingpongClient.cpp Task.o 
	g++ -o $@ $(CFLAGS) $^ -lpthread -lcommon


fileclient:Connection.o Client.o Server.o EventLoop.o Epoller.o InetAddress.o Socket.o fileClient.cpp Task.o 
	g++ -o $@ $(CFLAGS) $^ -lpthread -lcommon
fileserver:Connection.o Client.o Server.o EventLoop.o Epoller.o InetAddress.o Socket.o fileServer.cpp Task.o 
	g++ -o $@ $(CFLAGS) $^ -lpthread -lcommon

.PHONY:clean
clean:
	rm -rf ../src/*.o *.d *.o fileclient fileserver pingpongClient pingpongServer
