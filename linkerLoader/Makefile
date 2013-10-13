CC=g++
export CPLUS_INCLUDE_PATH=../common:./messages:.

export CPPFLAGS=\
		 -finline-functions \
		 -g \
		 -pipe \
		 -W \
		 -Wall \
		 -Werror \
		 -fPIC

export LDFLAGS=-lpthread -lcommon
export LIBRARY_PATH=../common

all:Inspector a.out test

Inspector:main.o messages/mesg.pb.o
	protoc messages/mesg.proto --cpp_out=.
	g++ -o $@ $^ $(CPPFLAGS) -L$(LIBRARY_PATH) $(LDFLAGS) -lelf -lprotobuf

test:test.o messages/mesg.pb.o
	g++ -o $@ $^ $(CPPFLAGS) -lprotobuf

a.out:SimpleSection.c
	gcc -o $@ $^ 

.PHONY:clean
clean:
	rm -rf Inspector *.o *Header test a.out
