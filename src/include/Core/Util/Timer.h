#pragma once

namespace ml {

class Timer {
public:
    Timer();
    Timer(int time);

    void start(int time);

    /**
     * Decrements the timer and returns true if the timer is done.
     * @return True if the timer has expired, false otherwise
     */
    bool update();

    void stop();

    void enable();
    void disable();

    bool isActive() const;
    bool isDone() const;

    bool isEnabled() const;
    bool isDisabled() const;

    int getTime() const;

private:
    int mTime = 0;
};

}
