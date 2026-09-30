#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <sys/epoll.h>
#include <sys/kqueue.h>
#include <unordered_map>
#include <map>
#include <vector>
#include <functional>
#include <memory>
#include "connection_pool.h"
#include "log.h"

// Event handler for epoll/kqueue
class EventHandler {
public:
    EventHandler();
    ~EventHandler();

    void start(const Config& config);
    void stop();

    void add_connection(std::shared_ptr<Connection> conn);
    void remove_connection(std::shared_ptr<Connection> conn);

private:
    int setup_epoll();
    int setup_kqueue();
    void handle_events();

    static void handle_read(int fd, void* arg);
    static void handle_write(int fd, void* arg);

    std::unordered_map<int, std::shared_ptr<Connection>> connections;
    std::map<int, std::pair<int, int>> epoll_events;
    std::map<int, std::pair<int, int>> kqueue_events;
    int epoll_fd;
    int kqueue_fd;
    std::unique_ptr<ConnectionPool> pool;
    std::unique_ptr<Logger> logger;
};

#endif // EVENT_HANDLER_H