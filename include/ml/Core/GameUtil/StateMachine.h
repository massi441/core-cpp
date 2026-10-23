#pragma once

#include <utility>

namespace ml {

template <typename T, typename ...Args>
class StateMachine {
public:
    using StateMachineFunc = void(T::*)(Args ...args);

    StateMachine() = default;

    explicit StateMachine(StateMachineFunc initialState) {
        mCurrentFunc = initialState;
    }

    template <typename ...F>
    void update(T* thisPtr, F&& ...args) const {
        (thisPtr->*mCurrentFunc)(std::forward<F>(args)...);
    }

    void setState(StateMachineFunc newState) {
        mCurrentFunc = newState;
    }

    bool isState(StateMachineFunc stateFunc) const {
        return stateFunc == mCurrentFunc;
    }

private:
    StateMachineFunc mCurrentFunc;
};

#define USE_STATE_MACHINE(T, ...)                                              \
    private:                                                                   \
        ml::StateMachine<T __VA_OPT__(,) __VA_ARGS__> mStateMachine;           \
                                                                               \
    public:                                                                    \
        ml::StateMachine<T __VA_OPT__(,) __VA_ARGS__>* getStateMachine() {     \
            return &mStateMachine;                                             \
        }                                                                      \
                                                                               \
        const ml::StateMachine<T __VA_OPT__(,) __VA_ARGS__>* getStateMachine() const { \
            return &mStateMachine;                                             \
        }                                                                      \

}
