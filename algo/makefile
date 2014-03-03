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

all-files=shuffle_array BinarySearchST quicksort stringSearch eightQueue 3sum generateNumber

#all:shuffle_array BinarySearchST quicksort stringSearch eightQueue
all:$(all-files)

shuffle_array:shuffle_array.cpp
	g++ $(INCPATH) -L$(LIBRARY_PATH) shuffle_array.cpp -o shuffle_array $(LDFLAGS)

BinarySearchST:BinarySearchST.cpp
	g++ $(INCPATH) -L$(LIBRARY_PATH) BinarySearchST.cpp -o BinarySearchST  $(LDFLAGS)

quicksort:quicksort.cpp
	g++ -g $(INCPATH) -L$(LIBRARY_PATH) quicksort.cpp -o quicksort  $(LDFLAGS)

stringSearch:stringSearch.cpp
	g++ $(INCPATH) -L$(LIBRARY_PATH) $^ -o $@  $(LDFLAGS)

eightQueue:eightQueue.cpp
	g++ $(INCPATH) -L$(LIBRARY_PATH) $^ -o $@  $(LDFLAGS) -std=c++0x

3sum:3sum.cpp
	g++ $(INCPATH) -L$(LIBRARY_PATH) $^ -o $@  $(LDFLAGS) -std=c++0x

generateNumber:generateNumber.cpp
	g++ $(INCPATH) -L$(LIBRARY_PATH) $^ -o $@  $(LDFLAGS) -std=c++0x

clean:
	rm -rf $(all-files)
