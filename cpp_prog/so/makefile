all:main

main:main.cpp libsubfunc1.so libsubfunc2.so libfunc.so libdeleter.so libmsg.so
	g++ main.cpp -o $@ -L. -lsubfunc1 -lsubfunc2 -lfunc -ldl -lmsg

func.o:func.cpp
	g++ -c $< -fPIC -o $@

subfunc1.o:subfunc1.cpp
	g++ -c $< -fPIC -o $@ 

subfunc2.o:subfunc2.cpp
	g++ -c $< -fPIC -o $@

deleter.o:deleter.cpp
	g++ -c $< -fPIC -o $@

msg.o:msg.cpp
	g++ -c $< -fPIC -o $@

libsubfunc1.so:subfunc1.o
	g++ $< -shared -o $@ 

libsubfunc2.so:subfunc2.o
	g++ $< -shared -o $@ 

libfunc.so:func.o
	g++ $< libsubfunc2.so -shared -o $@ 

libdeleter.so:deleter.o
	g++ $^ -shared -o $@

libmsg.so:msg.o
	g++ $^ -shared -o $@

.PHONY:clean
clean:
	rm -rf *.o *.so main
