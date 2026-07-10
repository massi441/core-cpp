#include "Core/Container/Array.h"

#include <cstring>

namespace ml {
    template <>
    bool Array<const char*>::contains(const char* const& item) const {
        const char* const* it = this->begin();
        const char* const* end = this->end();

        while (it != end) {
            if (*it == item) {
                return true;
            }

            if (strcmp(*it, item) == 0) {
                return true;
            }

            ++it;
        }

        return false;
    }
}
