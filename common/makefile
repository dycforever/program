
#export CPPFLAGS=-DDEBUG_LOG

VPATH=thread utils

INCLUDE_PATH=/home/dingyc/tools/log4c/include:/home/dingyc/github/program/common:/home/dingyc/github/program/common/utils
export CPLUS_INCLUDE_PATH=$(INCLUDE_PATH)


objects=common.o log.o ThreadPool.o Condition.o FileUtil.o DllWrapper.o
lib:$(objects)
	ar -q libcommon.a $(objects)

.PHONY:clean
clean:
	rm -rf *.o *.a
