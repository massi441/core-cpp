#pragma once

#include <unordered_map>

namespace ml {

template <typename TKey, typename TValue>
bool tryRemove(TValue* outValue, std::unordered_map<TKey, TValue>& map, const TKey& key) {
    auto it = map.find(key);

    if (it == map.end()) {
        return false;
    }

    *outValue = std::move(it->second);
    map.erase(it);

    return true;
}

template <typename T, typename ...Args>
T* placementNew(void* memory, Args&& ...args) {
    return new (memory) T(std::forward<Args>(args)...);
}

}
