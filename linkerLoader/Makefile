
.PHONY:all

all:
	protoc ./messages/mesg.proto --cpp_out=.
	make -j4 -C src
	cp -f src/Inspector .

clean:
	make clean -C src