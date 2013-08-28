CXX_FLAGS=-g -Werror -I../include

overloadNew:overloadNew.cpp
	g++ $^ $(CXX_FLAGS) -o $@ 

.PHONY:clean
clean:
	rm -rf *.o overloadNew
