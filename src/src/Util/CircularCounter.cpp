#include "Core/Util/CircularCounter.h"

#include "Core/Util/MathHelpers.h"

namespace ml {
    CircularCounter::CircularCounter(int min, int max) {
        mMin = min;
        mMax = max;
    }

    CircularCounter::CircularCounter(int min, int max, int initialValue) : CircularCounter(min, max) {
        mValue = initialValue;
    }

    void CircularCounter::setValue(int newValue) {
        if (MathHelpers<int>::isInRangeInclusive(newValue, mMin, mMax)) {
            mValue = newValue;
        }
    }

    void CircularCounter::increment() {
        int newValue = mValue + 1;
        mValue = MathHelpers<int>::loopVal(newValue, mMin, mMax);
    }

    void CircularCounter::increment(int times) {
        if (times <= 0) {
            return;
        }

        this->increment();
        this->increment(times - 1);
    }

    void CircularCounter::decrement() {
        int newValue = mValue - 1;
        mValue = MathHelpers<int>::loopVal(newValue, mMin, mMax);
    }

    void CircularCounter::decrement(int times) {
        if (times <= 0) {
            return;
        }

        this->decrement();
        this->decrement(times - 1);
    }
}
