export CPLUS_INCLUDE_PATH=../../common
export CPPFLAGS=\
		 -finline-functions \
		 -g \
		 -pipe \
		 -W \
		 -Wall \
		 -Werror \
		 -fPIC

export LDFLAGS=-lpthread
export LIBRARY_PATH=./
targets=adapter array inserter list map remove_if reverse_iter set test vector mem_func cWrapper

all:$(targets)
#	for t in $(targets);\
#	do\
#		g++ -o $$t $$t.cpp;\
#	done

.PHONY: clean
clean:
	rm $(targets)
