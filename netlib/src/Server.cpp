#include "Server.h"

namespace net {

    Server::Server(const InetAddress& listen_addr):
        m_listen_addr(listen_addr), m_init(false){}
    Server::~Server() {}

    int Server::init() {
        if (m_init)
            return 0;
        m_init = true;
        pthread_spin_init(&m_send_lock, PTHREAD_PROCESS_PRIVATE);
        pthread_spin_init(&m_recv_lock, PTHREAD_PROCESS_PRIVATE);
        m_thread_pool = NEW ThreadPool(3);
        int ret = m_thread_pool->init();
        return ret;
    }

    void Server::start() {
        m_listener->start();
        // push epoller
        Task* task = NEW EpollTask(m_poller);
        m_thread_pool->push_task(task);

        // push listener 
        AcceptParam* const param = NEW AcceptParam(m_listener->get_socket_obj(), m_listen_addr);
        task = NEW AcceptTask(param);
        m_thread_pool->push_task(task);
    }

    int Server::setup_listen() {
        if (init() != 0) {
            FATAL("init server failed");
            return -1;
        }
        m_listener = NEW Listener(m_listen_addr, this);
        if (m_listener->listen(m_listen_addr) == NULL) {
            FATAL("listen failed");
            return -1;
        }
        int ret = set_epoll();
        if (ret < 0) {
            FATAL("set epoll failed");
        }
        return 0;
    }

    int Server::set_epoll() {
        m_poller = NEW Epoller();
        if (m_poller == NULL) {
            FATAL("new socket failed");
            return -1;
        }
        int ret = m_poller->create_epoll_socket();
        return ret;
    }

    Connection* Server::new_connection(const InetAddress& peerAddr) {
        return new_connection(peerAddr, EPOLLIN | EPOLLOUT);
    }

    Connection* Server::new_connection(const InetAddress& peerAddr, uint32_t op_types) {
        //                                      SOCK_NONBLOCK 
        int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, IPPROTO_TCP);
        Socket* socket = NEW Socket(sockfd);
        if (sockfd < 0 || socket == NULL) {
            FATAL("invalid param: sockfd=%d   socket=%p", sockfd, socket);
            DELETE(socket);
            return NULL;
        }

        Connection* conn = NEW Connection(socket, peerAddr);
        if (conn == NULL) {
            DELETE(socket);
            FATAL("NEW conn failed");
            return NULL;
        }
        int ret = conn->connect();
        if (ret < 0) {
            sleep(2);
            DELETE(conn);
            DELETE(socket);
            FATAL("connect failed: %d", ret);
            return NULL;
        }
        m_poller->add_event(socket, op_types, conn);

        return conn;
    }
  
    void Server::remove_connection(const Connection& conn) {
//        m_fd_to_conn_map.erase(conn.get_socket()->get_socket());
    }

    int Server::remove_send_task(TransTask* task) {
        TaskQueue::iterator it = 
            std::find(m_send_task_queue.begin(), m_send_task_queue.end(), task);
        pthread_spin_lock(&m_send_lock);
        m_send_task_queue.erase(it);
        pthread_spin_unlock(&m_send_lock);
        return 0;
    }

    int Server::remove_recv_task(TransTask* task) {
        TaskQueue::iterator it = 
            std::find(m_recv_task_queue.begin(), m_recv_task_queue.end(), task);
        pthread_spin_lock(&m_recv_lock);
        m_recv_task_queue.erase(it);
        pthread_spin_unlock(&m_recv_lock);
        return 0;
    }

    TransTask* Server::get_send_task() {
        pthread_spin_lock(&m_send_lock);
        TransTask* task = m_send_task_queue.front();
        m_send_task_queue.pop_front();
        pthread_spin_unlock(&m_send_lock);
        return task;
    }

    TransTask* Server::get_recv_task() {
        pthread_spin_lock(&m_recv_lock);
        TransTask* task = m_recv_task_queue.front();
        m_recv_task_queue.pop_front();
        pthread_spin_unlock(&m_recv_lock);
        return task;
    }

    int Server::push_send_task(TransTask* task) {
        pthread_spin_lock(&m_send_lock);
        m_send_task_queue.push_back(task);
        pthread_spin_unlock(&m_send_lock);
        return 0;
    }

    int Server::push_recv_task(TransTask* task) {
        pthread_spin_lock(&m_recv_lock);
        m_recv_task_queue.push_back(task);
        pthread_spin_unlock(&m_recv_lock);
        return 0;
    }

}
