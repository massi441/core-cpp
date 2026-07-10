#pragma once

namespace ml {

class CircularCounter {
public:
    CircularCounter() = default;
    CircularCounter(int min, int max);
    CircularCounter(int min, int max, int initialValue);

    void setValue(int newValue);
    void increment();
    void increment(int times);
    void decrement();
    void decrement(int times);

    int getValue() const { return mValue; };

private:
    int mValue = 0;
    int mMin = 0;
    int mMax = 0;
};

}
