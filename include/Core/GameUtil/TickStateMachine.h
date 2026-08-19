#pragma once

#include <functional>

namespace ml {

template <typename T>
class TickStateMachine {
public:
    using StateFunc = void(T::*)();

    TickStateMachine() = default;

    explicit TickStateMachine(StateFunc initialState) {
        mCurrentFunc = initialState;
    }

    void update(T* thisPtr) {
        std::invoke(mCurrentFunc, thisPtr);

        if (!mIsStateChanged) {
            mTick++;
        } else {
            mIsStateChanged = false;
        }
    }

    void setState(StateFunc newState) {
        mCurrentFunc = newState;
        mIsStateChanged = true;
        mTick = 0;
    }

    bool isState(StateFunc stateFunc) const {
        return stateFunc == mCurrentFunc;
    }

    uint getTick() const {
        return mTick;
    }

    bool isFirstTick() const {
        return mTick == 0;
    }

    bool isTick(uint tick) const {
        return mTick == tick;
    }

    bool isOverTick(uint tickCount) const {
        return mTick > tickCount;
    }

    bool isOverEqualTick(uint tickCount) const {
        return mTick >= tickCount;
    }

private:
    StateFunc mCurrentFunc;
    uint mTick = 0;
    bool mIsStateChanged = false;
};

#define USE_TICK_STATE_MACHINE(T)                                    \
    private:                                                         \
        ml::TickStateMachine<T> mStateMachine;                       \
                                                                     \
    public:                                                          \
        ml::TickStateMachine<T>* getTickStateMachine() {             \
            return &mStateMachine;                                   \
        }                                                            \
                                                                     \
        const ml::TickStateMachine<T>* getTickStateMachine() const { \
            return &mStateMachine;                                   \
        }                                                            \

template <typename T>
void setState(T* t, typename TickStateMachine<T>::StateFunc newState) {
    t->getTickStateMachine()->setState(newState);
}

template <typename T>
bool isState(const T* t, typename TickStateMachine<T>::StateFunc stateFunc) {
    return t->getTickStateMachine()->isState(stateFunc);
}

template <typename T>
uint getTick(const T* t) {
    return t->getTickStateMachine()->getTick();
}

template <typename T>
bool isFirstTick(const T* t) {
    return t->getTickStateMachine()->isFirstTick();
}

template <typename T>
bool isTick(const T* t, uint tick) {
    return t->getTickStateMachine()->isTick(tick);
}

template <typename T>
bool isOverTick(const T* t, uint tickCount) {
    return t->getTickStateMachine()->isOverTick(tickCount);
}

template <typename T>
bool isOverEqualTick(const T* t, uint tickCount) {
    return t->getTickStateMachine()->isOverEqualTick(tickCount);
}

}
