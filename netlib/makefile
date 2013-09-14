export CPLUS_INCLUDE_PATH=../common
export CC=g++
export CFLAGS= -g -pipe -Wall -Werror -fPIC -I./include/ -I../common -L../common
VPATH=src

.PHONY:all
all: server client


server:Server.o EventLoop.o Epoller.o InetAddress.o Socket.o server.cpp
	g++ -o server $(CFLAGS) $^ -lpthread -lcommon

client:Server.o EventLoop.o Epoller.o InetAddress.o Socket.o client.cpp
	g++ -o client $(CFLAGS) $^ -lpthread -lcommon

Server.o:Server.cpp
	$(CC) $(CFLAGS) -c $< -o $@

InetAddress.o:InetAddress.cpp
	$(CC) $(CFLAGS) -c $< -o $@

EventLoop.o:EventLoop.cpp
	$(CC) $(CFLAGS) -c $< -o $@

Epoller.o:Epoller.cpp
	$(CC) $(CFLAGS) -c $< -o $@

#Connection.o:Connection.cpp
#	$(CC) $(CFLAGS) -c $< -o $@

#Listener.o:Listener.cpp
#	$(CC) $(CFLAGS) -c $< -o $@

#Server.o:Server.cpp
#	$(CC) $(CFLAGS) -c $< -o $@

Socket.o:Socket.cpp
	$(CC) $(CFLAGS) -c $< -o $@

ThreadPool.o:ThreadPool.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	rm -rf src/*.o *.d *.o server client test
