CC=g++
export CPLUS_INCLUDE_PATH=../common:./messages:.:/home/dyc/tools/python3-protobuf_src/src/

export CPPFLAGS=\
		 -finline-functions \
		 -g \
		 -pipe \
		 -W \
		 -Wall \
		 -Werror \
		 -fPIC

export LDFLAGS=-lcommon -lpthread 
export LIBRARY_PATH=../common:/home/dyc/tools/python3-protobuf/lib/

all:Inspector a.out test

Inspector:main.o messages/mesg.pb.o
	protoc messages/mesg.proto --cpp_out=.
	g++ -o $@ $^ $(CPPFLAGS) -L$(LIBRARY_PATH) $(LDFLAGS) -lelf -lprotobuf

test:test.o messages/mesg.pb.o
	g++ -o $@ $^ $(CPPFLAGS) -L$(LIBRARY_PATH) $(LDFLAGS) -lelf -lprotobuf

a.out:SimpleSection.c
	gcc -o $@ $^ 

.PHONY:clean
clean:
	rm -rf Inspector *.o *Header test a.out
