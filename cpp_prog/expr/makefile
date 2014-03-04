export CPLUS_INCLUDE_PATH=../../common
export CPPFLAGS=\
		 -finline-functions \
		 -g \
		 -pipe \
		 -W \
		 -Wall \
		 -Werror \
		 -fPIC \
#		 -std=c++0x

export LDFLAGS=-lpthread
export LIBRARY_PATH=./

targets=boolAddress constFuc constRef inherit_size \
		inh_v init iplusplus operatorOverload \
		order1 sizeof snprintf stack8 templates 


all:$(targets)

.PHONY:clean
clean:
	rm -rf *.o $(targets)

