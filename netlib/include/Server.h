#ifndef NETLIB_Server_H
#define NETLIB_Server_H

#include <map>
#include <vector>
#include <list>
#include <algorithm>

#include "InetAddress.h" 
#include "Socket.h" 
#include "Epoll.h"
#include "Task.h"

namespace net {

class Listener;

class Service {
    Callback rvcb;
    MallocCallback mcb;
};


///
/// TCP server, supports single-threaded and thread-pool models.
///
/// This is an interface class, so don't expose too much details.
class Server {
 public:

  //Server(EventLoop* loop, const InetAddress& listenAddr);
  Server(const InetAddress& listenAddr);
  ~Server();  // force out-line dtor, for scoped_ptr members.

//  const InetAddress& host_address() const { return m_listenAddr; }

  void set_threadNum(int numThreads);

  /// Starts the server if it's not listenning.
  ///
  /// It's harmless to call it multiple times.
  /// Thread safe.
  void start();
  int setup_listen();
  TransTask* get_send_task();
  TransTask* get_recv_task();

  int push_send_task(TransTask*);
  int push_recv_task(TransTask*);

  /// Not thread safe, but in loop
  Socket* new_connection(const InetAddress& peerAddr, uint32_t);
  Socket* new_connection(const InetAddress& peerAddr);
//  /// Thread safe.
  void remove_connection(const Socket& conn);

  int remove_send_task(TransTask*);
  int remove_recv_task(TransTask*);

  //for debug
  ThreadPool* m_thread_pool;
  int init();
  int add_to_epoll(Socket* sockfd, struct epoll_event&);
  int set_epoll();

private:
  const InetAddress m_listen_addr;
  bool m_init;
  Listener* m_listener;

  Epoller* m_poller;

  TaskQueue m_send_task_queue;
  TaskQueue m_recv_task_queue;
  pthread_spinlock_t m_send_lock;
  pthread_spinlock_t m_recv_lock;

};

}

#endif  
