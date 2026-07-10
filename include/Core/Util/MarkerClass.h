#pragma once

#include <utility>

namespace ml {

/**
 * A safe way to declare a marker class. Useful for adding member functions to an existing class,
 * and use those functions in hooks on 'this' pointers. A compilation error is thrown if the
 * marker class accidentally adds any extra fields, preventing catastrophic UB.
 * @tparam T The derived class, used for the CRTP pattern
 * @tparam B The base class to inherit, that the derived class is 'marking'
 */
template <typename T, typename B>
class MarkerClass : public B {
public:
    template <typename ...Args>
    MarkerClass(Args&&... args) : B(std::forward<Args>(args)...) {
        static_assert(sizeof(T) == sizeof(B), "ERROR: A marker class should not have any additional fields");
    }
};

}
