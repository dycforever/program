CC=g++
export CPLUS_INCLUDE_PATH=../common/
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

all:Inspector test a.out

Inspector:Inspector.o Header.o ProgramHeader.o SectionHeader.o  
	g++ -o $@ $^ $(CPPFLAGS) -L$(LIBRARY_PATH) -I$(CPLUS_INCLUDE_PATH) $(LDFLAGS) -lelf

test:test.o Header.o
	g++ -o $@ $^ $(CPPFLAGS) -L$(LIBRARY_PATH) -I$(CPLUS_INCLUDE_PATH) $(LDFLAGS) -lelf

a.out:SimpleSection.c
	gcc -o $@ $^ 

.PHONY:clean
clean:
	rm -rf Inspector *.o *Header test a.out
