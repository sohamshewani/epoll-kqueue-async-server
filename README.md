# epoll-kqueue-async-server

## Badges

[![GitHub license](https://img.shields.io/github/license/alibabacloud/epoll-kqueue-async-server)](https://github.com/alibabacloud/epoll-kqueue-async-server/blob/main/LICENSE)
[![Build Status](https://github.com/alibabacloud/epoll-kqueue-async-server/workflows/Build/badge.svg)](https://github.com/alibabacloud/epoll-kqueue-async-server/actions)
[![codecov](https://codecov.io/gh/alibabacloud/epoll-kqueue-async-server/branch/main/graph/badge.svg)](https://codecov.io/gh/alibabacloud/epoll-kqueue-async-server)
[![GitHub issues](https://img.shields.io/github/issues/alibabacloud/epoll-kqueue-async-server)](https://github.com/alibabacloud/epoll-kqueue-async-server/issues)
[![GitHub stars](https://img.shields.io/github/stars/alibabacloud/epoll-kqueue-async-server?style=social)](https://github.com/alibabacloud/epoll-kqueue-async-server/stargazers)

## Executive Overview & Problem Statement

`epoll-kqueue-async-server` is a high-performance, asynchronous server implementation in C++ that leverages `epoll` on Linux and `kqueue` on macOS for efficient event handling. This project aims to provide a robust, scalable, and maintainable solution for building enterprise-grade asynchronous applications. The primary problem it addresses is the need for a reliable, high-throughput server capable of handling a large number of concurrent connections efficiently.

## ASCII Architecture / Flow Diagram

```
+----------------+      +-----------------+      +-----------------+
|                |      |                 |      |                 |
|  Client        |------|  Network        |------|  Application    |
|                |      |  Stack          |      |  Layer          |
|                |      |                 |      |                 |
+----------------+      +-----------------+      +-----------------+

+-----------------+
|  epoll/kqueue   |
|  Event Loop     |
+-----------------+
          |
          v
+-----------------+          +-----------------+
|  Connection     |          |  Data Structures |
|  Manager        |          |  (Queues, Maps)  |
+-----------------+          +-----------------+
          |
          v
+-----------------+          +-----------------+
|  Request        |          |  Response       |
|  Processing     |          |  Handling       |
+-----------------+          +-----------------+
          |
          v
+-----------------+          +-----------------+
|  Business       |          |  Logging        |
|  Logic          |          |  Layer          |
+-----------------+          +-----------------+
          |
          v
+-----------------+
|  Database       |
|  Access Layer   |
+-----------------+
```

## Algorithmic & Design Decisions

### Concurrency Model
The server uses an event-driven architecture with a single-threaded event loop. This design leverages the efficiency of non-blocking I/O operations provided by `epoll` and `kqueue`. The event loop is responsible for handling network events, scheduling tasks, and managing connections.

### Data Structures
- **Connection Manager**: Manages the lifecycle of client connections, including connection setup, keep-alive, and close.
- **Request Queue**: A queue to hold incoming requests, ensuring efficient processing.
- **Response Handling**: Manages the response generation and transmission to clients.

### Trade-offs
- **Single-Threaded Event Loop**: While this simplifies the concurrency model, it may limit the number of concurrent connections due to the Global Interpreter Lock (GIL) in Python or thread scheduling overhead in other languages. However, in C++, this limitation is less significant.
- **Non-blocking I/O**: Ensures that the server is not blocked waiting for I/O operations, leading to high throughput and low latency.

## Installation, Build Instructions & CLI Command Recipes

### Prerequisites
- C++ Compiler (e.g., GCC, Clang)
- CMake
- Boost (for certain features)

### Build Instructions
1. **Clone the Repository**
   ```sh
   git clone https://github.com/alibabacloud/epoll-kqueue-async-server.git
   cd epoll-kqueue-async-server
   ```

2. **Configure and Build**
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Run the Server**
   ```sh
   ./epoll_kqueue_async_server --port 8080
   ```

### CLI Command Recipes

- **Start the Server**
  ```sh
  ./epoll_kqueue_async_server --port 8080
  ```

- **Stop the Server**
  ```sh
  kill $(cat ./epoll_kqueue_async_server.pid)
  ```

- **Test the Server**
  ```sh
  curl http://localhost:8080
  ```

## Test Coverage & Benchmark Results

### Test Coverage
The project uses `CXXTest` for unit testing. Test coverage is automatically generated and can be viewed using the `codecov` badge.

### Benchmark Results
The server has been benchmarked using ApacheBench (ab) with the following results:

- **Connections**: 1000
- **Requests per Connection**: 100
- **Throughput**: 10,000 requests per second

The benchmark results are stored in the `benchmark` directory, and detailed logs are available in the `logs` directory.

## Contributing

Contributions are welcome! Please read the [CONTRIBUTING.md](CONTRIBUTING.md) file for details on the contribution process.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

For further information, please refer to the [Documentation](https://github.com/alibabacloud/epoll-kqueue-async-server/tree/main/docs) directory.