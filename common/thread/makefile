
#export CPPFLAGS=-DDEBUG_LOG

COM_LIB_PATH=/home/dyc/tools/log4c/include
export CPLUS_INCLUDE_PATH=$(COM_LIB_PATH)


objects=ThreadPool.o ThreadPool.o
lib:$(objects)
	ar -q libcommon.a $(objects)

.PHONY:clean
clean:
	rm -rf *.o *.a
