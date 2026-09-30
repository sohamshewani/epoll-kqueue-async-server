#include "log.h"
#include <iostream>
#include <mutex>

using namespace std;

Logger::Logger(const string& file_path) : log_file(file_path, ios::out | ios::app) {
}

Logger::~Logger() {
    log_file.close();
}

void Logger::log_info(const string& message) {
    lock_guard<mutex> lock(log_mutex);
    log_file << "[INFO] " << message << endl;
    cout << "[INFO] " << message << endl;
}

void Logger::log_error(const string& message) {
    lock_guard<mutex> lock(log_mutex);
    log_file << "[ERROR] " << message << endl;
    cout << "[ERROR] " << message << endl;
}
