#include "Engine/Timer.h"

Timer::Timer(float time) {
    m_time = time;
}

void Timer::Start() {
    m_running = true;
    std::thread timer_thread([this]() {
        std::this_thread::sleep_for(std::chrono::seconds(m_time));
        m_running = false;
    });
    timer_thread.detach();
}

void Timer::setTime(float time) {
    m_time = time;
}

bool Timer::isRunning() {
    return m_running;
}
