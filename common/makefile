all:lib rawloglib

VPATH=thread utils

INCLUDE_PATH=/home/dyc/tools/log4c/include:/home/dyc/github/program/common
export CPLUS_INCLUDE_PATH=$(INCLUDE_PATH)


objects=common.o ThreadPool.o FileUtil.o DllWrapper.o LoopThread.o StringTokenizer.o StringUtil.o 
lib:$(objects)
	ar -q libcommon.a $(objects)

# export CPPFLAGS=-DUSE_LOG4C
rawloglib:rawlog.o 
	ar -q librawlog.a rawlog.o

.PHONY:clean
clean:
	rm -rf *.o *.a


