# add -fno-common will forbid common model in gcc, example:
# gcc -fno-common main.c foo.c
test: main.o foo.o
	gcc -o test main.o foo.o 

main.o: main.c
foo.o: foo.c

clean:
	rm *.o test
