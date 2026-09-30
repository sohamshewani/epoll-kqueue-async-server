#include "config.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

Config load_config(const string& config_file) {
    ifstream config_stream(config_file);
    if (!config_stream.is_open()) {
        throw runtime_error("Failed to open config file");
    }

    Config config;
    string line;
    while (getline(config_stream, line)) {
        istringstream iss(line);
        string key, value;
        iss >> key >> value;
        if (key == "server_address") {
            config.server_address = value;
        } else if (key == "port") {
            config.port = stoi(value);
        } else if (key == "log_file_path") {
            config.log_file_path = value;
        } else if (key == "max_connections") {
            config.max_connections = stoi(value);
        } else if (key == "timeout") {
            config.timeout = stoi(value);
        }
    }
    return config;
}
