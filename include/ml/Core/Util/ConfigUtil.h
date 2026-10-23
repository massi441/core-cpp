#pragma once

#ifndef NN_SWITCH

#include <filesystem>
#include <functional>
#include <string>

namespace ml {

bool parseConfig(const std::filesystem::path& path, const std::function<void(const std::string& key, const std::string& value)>& kvParser, char kvDelimiter = '=');

}

#endif
