#pragma once

#include <functional>

namespace ml {

template <typename T>
class StateMachine {
public:
    using StateMachineFunc = void(T::*)();

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

}
