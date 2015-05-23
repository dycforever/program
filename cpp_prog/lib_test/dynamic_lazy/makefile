
all: main main_lazy main_link

test:test.cpp 
	g++ -shared -fPIC -o libtest.so test.cpp 

main: main.cpp test 
	g++ $< -o $@ -ldl

main_lazy: main.cpp test 
	g++ $< -DLAZY -o $@ -ldl

# will fail
main_link: main_fail.cpp test 
	g++ $< -L. -ltest -o $@

clean:
	rm -rf *.a *.o *.so a.out main main_l*

