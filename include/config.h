#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>

// Configuration settings
struct Config {
    std::string server_address;
    int port;
    std::string log_file_path;
    int max_connections;
    int timeout;
};

// Load configuration from file
Config load_config(const std::string& config_file);

#endif // CONFIG_H