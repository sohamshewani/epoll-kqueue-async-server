#ifndef CONNECTION_POOL_H
#define CONNECTION_POOL_H

#include <unordered_map>
#include <functional>
#include <memory>
#include "log.h"

// Connection pool for managing reusable connections
class ConnectionPool {
public:
    ConnectionPool(int max_connections);
    ~ConnectionPool();

    std::shared_ptr<Connection> get_connection();
    void release_connection(std::shared_ptr<Connection> conn);

private:
    std::unordered_map<int, std::shared_ptr<Connection>> connections;
    int max_connections;
    std::unique_ptr<Logger> logger;
};

#endif // CONNECTION_POOL_H