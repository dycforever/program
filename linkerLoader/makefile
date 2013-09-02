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

all:Inspector

Inspector:Inspector.o Header.o ProgramHeader.o SectionHeader.o  
	g++ -o $@ $^ $(CPPFLAGS) -L$(LIBRARY_PATH) -I$(CPLUS_INCLUDE_PATH) $(LDFLAGS) -lelf

.PHONY:clean
clean:
	rm -rf Inspector *.o *Header
