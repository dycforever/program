all:main main2
main:main.o lib.so
	$(CC) main.o lib.so -o main
main2:main.o lib.o
	$(CC) main.o lib.o -o main2
lib.so:lib.c
	$(CC) lib.c -shared -o lib.so
lib.o:lib.c
	$(CC) lib.c -c
subsystem:
	cd sub1 && make 
	cd sub2 && make

.PHONY:clean
clean:
	rm *.o 
