#include "event_handler.h"
#include <sys/epoll.h>
#include <sys/kqueue.h>
#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h>
#include <poll.h>
#include <errno.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>

using namespace std;

EventHandler::EventHandler() : epoll_fd(-1), kqueue_fd(-1) {
    logger = std::make_unique<Logger>("log.txt");
}

EventHandler::~EventHandler() {
    stop();
}

void EventHandler::start(const Config& config) {
    try {
        epoll_fd = setup_epoll();
        kqueue_fd = setup_kqueue();
        pool = std::make_unique<ConnectionPool>(config.max_connections);
        logger->log_info("Server started");
    } catch (const std::exception& e) {
        logger->log_error("Server startup failed: " + std::string(e.what()));
        throw;
    }
}

void EventHandler::stop() {
    if (epoll_fd != -1) {
        close(epoll_fd);
        epoll_fd = -1;
    }
    if (kqueue_fd != -1) {
        close(kqueue_fd);
        kqueue_fd = -1;
    }
    if (pool) {
        pool->~ConnectionPool();
    }
}

void EventHandler::add_connection(std::shared_ptr<Connection> conn) {
    connections[conn->get_fd()] = conn;
    epoll_events[conn->get_fd()] = std::make_pair(EPOLLIN | EPOLLET, 0);
    kqueue_events[conn->get_fd()] = std::make_pair(KERN_READ, 0);
}

void EventHandler::remove_connection(std::shared_ptr<Connection> conn) {
    connections.erase(conn->get_fd());
    epoll_events.erase(conn->get_fd());
    kqueue_events.erase(conn->get_fd());
}

int EventHandler::setup_epoll() {
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        throw std::runtime_error("Failed to create epoll instance");
    }
    return epoll_fd;
}

int EventHandler::setup_kqueue() {
    kqueue_fd = kqueue();
    if (kqueue_fd == -1) {
        throw std::runtime_error("Failed to create kqueue instance");
    }
    return kqueue_fd;
}

void EventHandler::handle_events() {
    while (true) {
        // Event handling logic here
    }
}

void EventHandler::handle_read(int fd, void* arg) {
    // Handle read event
}

void EventHandler::handle_write(int fd, void* arg) {
    // Handle write event
}
