
rm -rf *.so *.a *.c main

g++ ssl1.cpp -fPIC -shared -o libssl.so
g++ curl.cpp -fPIC -shared -o libcurl.so ./libssl.so

g++ -c curl.cpp -o curl.o 
ar -q libcurl.a curl.o

g++ -c ssl2.cpp -o ssl2.o
ar -q libssl.a ssl2.o

g++ main.cpp -o main libssl.a libcurl.a
g++ main.cpp -o main libcurl.a libssl.a
./main

