
all: main lib1 lib2

global.o: global.cpp
	g++ -c global.cpp 

lib1.o: lib1.cpp
	g++ -c lib1.cpp 

lib2.o: lib2.cpp
	g++ -c lib2.cpp 

lib1:lib1.o global.o
	ar -q liblib1.a lib1.o global.o

lib2:lib2.o global.o
	ar -q liblib2.a lib2.o global.o

main: main.cpp lib1 lib2
	g++ main.cpp -L. -llib1 -llib2


clean:
	rm -rf *.o *.a a.out
