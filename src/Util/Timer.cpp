#pragma once

#include "Core/Util/Timer.h"

// TODO: Inline in header

namespace ml {

Timer::Timer() {

}

Timer::Timer(int time) {
    mTime = time;
}

void Timer::start(int time) {
    if (time < 0) {
        this->disable();
        return;
    }

    mTime = time;
}

bool Timer::update() {
    if (this->isActive()) {
        mTime--;
    }

    return this->isDone();
}

void Timer::stop() {
    mTime = 0;
}

void Timer::enable() {
    mTime = 0;
}

void Timer::disable() {
    mTime = -1;
}

bool Timer::isActive() const{
    return mTime > 0;
}

bool Timer::isDone() const {
    return mTime == 0;
}

bool Timer::isEnabled() const {
    return mTime != -1;
}

bool Timer::isDisabled() const {
    return mTime == -1;
}

int Timer::getTime() const {
    return mTime;
}

}
