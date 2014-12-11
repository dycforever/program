
all: main_link main_dlopen

lib1:lib1.cpp global.cpp
	g++ -shared -fPIC -o liblib1.so lib1.cpp global.cpp

lib2:lib2.cpp global.cpp
	g++ -shared -fPIC -o liblib2.so lib2.cpp global.cpp

main_link: main.cpp lib1 lib2
	g++ $< -L. -llib1 -llib2 -o $@

main_dlopen: main.cpp lib1 lib2
	g++ $< -DDLOPEN -o $@ -ldl

clean:
	rm -rf *.a *.o *.so a.out main_dlopen main_link

