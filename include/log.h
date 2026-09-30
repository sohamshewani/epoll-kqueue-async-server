#ifndef LOG_H
#define LOG_H

#include <string>
#include <fstream>
#include <iostream>
#include <mutex>

// Logging class for error and informational messages
class Logger {
public:
    Logger(const std::string& file_path);
    ~Logger();

    void log_info(const std::string& message);
    void log_error(const std::string& message);

private:
    std::ofstream log_file;
    std::mutex log_mutex;
};

#endif // LOG_H