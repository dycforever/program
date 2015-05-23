
INCPATH=-I. -I../common

CXXFLAGS=-O1 \
		 -finline-functions \
		 -g \
		 -pipe \
		 -W \
		 -Wall \
		 -Werror \
		 -fPIC

export LDFLAGS=-lcommon -lpthread -lrawlog
export LIBRARY_PATH=../common

srcFiles=shuffle_array.cpp BinarySearchST.cpp quicksort.cpp stringSearch.cpp eightQueue.cpp 3sum.cpp generateNumber.cpp

empty=
source_suffix=.cpp
obj_suffix=.o


binfiles=$(subst $(source_suffix),$(empty),$(srcFiles))
objfiles=$(subst $(source_suffix),$(obj_suffix),$(srcFiles))


all:$(binfiles)
$(binfiles):%:%.cpp
	g++ -g $(INCPATH) -L$(LIBRARY_PATH) $< -o $@ $(LDFLAGS)

clean:
	for file in $(binfiles) ; do \
		rm -rf $$file $$file.o ;\
	done

