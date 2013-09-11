#ifndef NETLIB_LISTENER_H
#define NETLIB_LISTENER_H

#include <list>
#include <sys/socket.h>

#include "Server.h"
#include "Connection.h"
#include "util.h"

namespace net {

class Listener {
public:
    Listener(const InetAddress& addr, Server* server);
    void loop();
    void start();
    void stop();

    int init();

    Socket* listen(const InetAddress& addr);

    int listen(Socket* socket, const InetAddress& addr);
    int get_socket();
    Socket* get_socket_obj() {
        return m_listen_socket;
    }
private:
    Server* m_server;
    Socket* m_listen_socket;
    Socket* setup_server(const InetAddress& addr);
};

}

#endif  
