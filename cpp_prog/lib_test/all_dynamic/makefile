
all: main lib1 lib2

libglobal.so:global.cpp
	g++ -shared -fPIC -o libglobal.so global.cpp

lib1:lib1.cpp libglobal.so
	g++ -shared -fPIC -o liblib1.so lib1.cpp -L. -lglobal

lib2:lib2.cpp libglobal.so
	g++ -shared -fPIC -o liblib2.so lib2.cpp -L. -lglobal

main: main.cpp lib1 lib2
	g++ main.cpp -L. -llib1 -llib2 -lglobal

clean:
	rm -rf *.a *.o *.so a.out
