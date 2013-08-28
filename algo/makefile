INCPATH=-I. -I../include

CXXFLAGS=-O1 \
		 -finline-functions \
		 -g \
		 -pipe \
		 -W \
		 -Wall \
		 -Werror \
		 -fPIC

all:shuffle_array BinarySearchST quicksort stringSearch eightQueue

shuffle_array:shuffle_array.cpp
	g++ $(INCPATH) shuffle_array.cpp -o shuffle_array 

BinarySearchST:BinarySearchST.cpp
	g++ $(INCPATH) BinarySearchST.cpp -o BinarySearchST 

quicksort:quicksort.cpp
	g++ $(INCPATH) quicksort.cpp -o quicksort 

stringSearch:stringSearch.cpp
	g++ $(INCPATH) $^ -o $@ 

eightQueue:eightQueue.cpp
	g++ $(INCPATH) $^ -o $@ 
