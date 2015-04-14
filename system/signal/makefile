
.PHONY: all

all: signaltest forktest

signaltest: main.cpp signal_event_loop.cpp
	g++ main.cpp signal_event_loop.cpp -o signaltest 

forktest: forktest.cpp signal_event_loop.cpp
	g++ forktest.cpp signal_event_loop.cpp -o forktest
