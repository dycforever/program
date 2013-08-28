all:graph search path 


graph:graph.cpp graph.h
	g++ graph.cpp -I../../cpp_prog/include -I. -o $@

search:Search.cpp graph.h
	g++ -o $@ $^ -I../../cpp_prog/include -I.

path:Path.cpp graph.h
	g++ -o $@ $^ -I../../cpp_prog/include -I.
