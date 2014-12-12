
all: main main_lazy

test:test.cpp 
	g++ -shared -fPIC -o libtest.so test.cpp 

main: main.cpp test 
	g++ $< -o $@ -ldl

main_lazy: main.cpp test 
	g++ $< -DLAZY -o $@ -ldl

clean:
	rm -rf *.a *.o *.so a.out main main_lazy

