export LD_LIBRARY_PATH:=.

all: test
	./test

test: t1.o t2.o
	gcc -shared -fPIC -o libfoo.so foo.c
	gcc -o test t1.o t2.o -L. -lfoo

t1.o: t1.c
t2.o: t2.c

.PHONY:clean
clean:
	rm -f *.o *.so test*
