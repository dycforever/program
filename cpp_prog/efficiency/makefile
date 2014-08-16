all:cache_line

export CPLUS_INCLUDE_PATH=-I/home/dyc/github/program/common

cache_line:cache_line.cpp
	g++ $(CPLUS_INCLUDE_PATH) $^ -o $@ 

.PHONY:clean
clean:
	rm cache_line

