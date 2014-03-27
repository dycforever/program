
INCPATH=-I. -I../common

CXXFLAGS=-O1 \
		 -finline-functions \
		 -g \
		 -pipe \
		 -W \
		 -Wall \
		 -Werror \
		 -fPIC

export LDFLAGS=-lcommon -lpthread 
export LIBRARY_PATH=../common

srcFiles=eventfd.c ptrace.c

empty=
source_suffix=.c
obj_suffix=.o


binfiles=$(subst $(source_suffix),$(empty),$(srcFiles))
objfiles=$(subst $(source_suffix),$(obj_suffix),$(srcFiles))


all:$(binfiles)
$(binfiles):%:%.c
	gcc -g $(INCPATH) -L$(LIBRARY_PATH) $< -o $@ $(LDFLAGS)

clean:
	for file in $(binfiles) ; do \
		rm -rf $$file $$file.o ;\
	done


