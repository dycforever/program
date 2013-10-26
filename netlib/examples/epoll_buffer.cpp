
#include <sys/eventfd.h>
#include <pthread.h>

#include "common.h"
#include "netlib.h"

using namespace std;
using namespace dyc;


void* epollThread(void* efd) {
    NOTICE("thread run");
	Epoller poller;
	poller.createEpoll();
	
	int ret = poller.addRead(NEW Socket((int)efd));
	CHECK_ERROR((void*)-1, ret==0, "addRead() failed");

	Epoller::Event event;
	event.data.fd = (int)efd;
	while (true) {
		ret = poller.poll(&event);
		CHECK_ERRORNO((void*)-1, ret==1, "poll() failed");
		long long i;
		if (event.events | EPOLLIN) {
			int ret = read(event.data.fd, &i, sizeof(i));
			NOTICE("epoll read %d bytes i:%lld", ret, i);
		}
        break;
	}
    return NULL;
}

int main() {

	int efd = eventfd(0, 0);
	CHECK_ERRORNO(-1, efd>0, "eventfd() failed");
	pthread_t pid;
//	pthread_create(&pid, NULL, epollThread, (void*)efd);
    int child = fork();
    if (child == 0) {
        epollThread((void*)efd);
    }
    else {
        sleep(2);
    	while(true) {
            NOTICE("please input:");
            getchar();
            getchar();
            long long i=1234;
            int ret = write(efd, &i, sizeof(i));
    		CHECK_ERRORNO(-1, ret==sizeof(i), "write() efd[%d] failed ret:%d", efd, ret);
    		NOTICE("write %d bytes i:%lld", ret, i);
    	}
    }
}

