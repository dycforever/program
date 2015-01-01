
make clean

g++ -c global.cpp 
g++ -c lib1.cpp 
ar -q liblib1.a lib1.o global.o
md5sum ./global.o

rm -rf global.o
g++ -c global.cpp 
md5sum ./global.o
g++ -c lib2.cpp 
ar -q liblib2.a lib2.o global.o
g++ main.cpp -L. -llib1 -llib2

./a.out

