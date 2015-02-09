
all: main_link main_dlopen main_link_print_var main_link_print_var_pic

lib1:lib1.cpp global.cpp
	g++ -g -shared -fPIC -o liblib1.so lib1.cpp global.cpp

lib2:lib2.cpp global.cpp
	g++ -g -shared -fPIC -o liblib2.so lib2.cpp global.cpp

main_dlopen: main.cpp lib1 lib2
	g++ -g $< -DDLOPEN -o $@ -ldl

main_link_print_var_pic: main.cpp lib1 lib2
	g++ -g -fPIC $< -DPRINT_VAR -L. -llib1 -llib2 -o $@

main_link_print_var: main.cpp lib1 lib2
	g++ -g $< -DPRINT_VAR -L. -llib1 -llib2 -o $@

main_link: main.cpp lib1 lib2
	g++ -g $< -L. -llib1 -llib2 -o $@

clean:
	rm -rf *.a *.o *.so a.out main_dlopen main_link*

