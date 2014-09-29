all:cache_line hashmap_prof stdmap_prof

export CPLUS_INCLUDE_PATH=-I/home/dyc/github/program/common

cache_line: cache_line.cpp
	g++ $(CPLUS_INCLUDE_PATH) $^ -o $@ 

hashmap_prof: map_prof.cpp
	g++ $(CPLUS_INCLUDE_PATH) -DTEST_HASH_MAP $^ -o $@ 

stdmap_prof: map_prof.cpp
	g++ $(CPLUS_INCLUDE_PATH) -DTEST_STD_MAP $^ -o $@ 

.PHONY:clean
clean:
	rm cache_line

