#include "utils.h"
#include <chrono>
#include <iomanip>

using namespace std;

std::string format_time() {
    return std::chrono::system_clock::now().time_since_epoch().count();
}

bool is_valid_ip(const std::string& ip) {
    // IP validation logic
}
