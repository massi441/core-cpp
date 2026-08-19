#pragma once

#include <functional>

namespace ml {

template <typename T>
class StateMachine {
public:
    using StateMachineFunc = void(T::*)();

    StateMachine() = default;

    explicit StateMachine(StateMachineFunc initialState) {
        mCurrentFunc = initialState;
    }

    void update(T* thisPtr) const {
        std::invoke(mCurrentFunc, thisPtr);
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

#define USE_STATE_MACHINE(T)                               \
    private:                                               \
        ml::StateMachine<T> mStateMachine;                 \
                                                           \
    public:                                                \
        ml::StateMachine<T>* getStateMachine() {           \
            return &mStateMachine;                         \
        }                                                  \
                                                           \
        const ml::StateMachine<T>* getStateMachine() const {  \
            return &mStateMachine;                         \
        }                                                  \

// template <typename T, typename StateFunc>
// void setState(T* t, StateFunc newState) {
//     t->getStateMachine()->setState(newState);
// }
//
// template <typename T, typename StateFunc>
// bool isState(const T* t, StateFunc stateFunc) {
//     return t->getStateMachine()->isState(stateFunc);
// }

}
