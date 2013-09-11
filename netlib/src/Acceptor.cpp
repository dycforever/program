#include "Listener.h"

namespace net {

    Listener::Listener(const InetAddress& addr, Server* server):
    m_server(server){
    }

    Socket* Listener::listen(const InetAddress& addr){
    	int check;
    	int sfd = socket(AF_INET,SOCK_STREAM,0);
        m_listen_socket = NEW Socket(sfd);

        check = m_listen_socket->bindAddress(addr);
    	if(check < 0){
    		FATAL("bind error \n");
            return NULL;
    	}

    	check = m_listen_socket->listen();
    	if(check < 0){
    		FATAL("listen error \n");
            return NULL;
    	}
//        NOTICE("listen success");
        return m_listen_socket;
    }


    int Listener::init() {
        return 0;
    }

    void Listener::start() {
    }
    void Listener::stop() {
    }


// the inline assembler code makes type blur,
// so we disable warnings for a while.
#if __GNUC_MINOR__ >= 6
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wold-style-cast"

    int Listener::get_socket() {
        return m_listen_socket->get_socket();
    }
    // bind and listen
    int Listener::listen(Socket* socket, const InetAddress& addr) {
    	int check;
    	int sfd = socket->get_socket();
        const struct sockaddr_in& servaddr = addr.getSockAddrInet();
        const SA* sa = sockaddr_cast(&servaddr);
        check = bind(sfd, sa, sizeof(servaddr));
    
    	if(check < 0){
    		FATAL("bind error \n");
            return -1;
    	}
        NOTICE("bind success");
    
    	check = ::listen(sfd, SOMAXCONN);
    	if(check < 0){
    		FATAL("listen error \n");
            return -1;
    	}
//        NOTICE("listen success");
        return 0;
    }

#if __GNUC_MINOR__ >= 6
#pragma GCC diagnostic pop
#else
#pragma GCC diagnostic error "-Wconversion"
#pragma GCC diagnostic error "-Wold-style-cast"
#endif

} // namespace

