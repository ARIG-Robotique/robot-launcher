#ifndef ROBOT_LAUNCHER_COMMON_H
#define ROBOT_LAUNCHER_COMMON_H

#include <iostream>
#include "json.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

using namespace std;
using json = nlohmann::json;


struct JsonConfig {
    json data;
};

#endif //ROBOT_LAUNCHER_COMMON_H
