#pragma once

#ifndef NN_SWITCH

#include <functional>
#include <string>
#include <fstream>

namespace ml {

bool parseConfig(const std::string& path, const std::function<void(const std::string& key, const std::string& value)>& kvParser, char kvDelimiter = '=');

}

#endif
