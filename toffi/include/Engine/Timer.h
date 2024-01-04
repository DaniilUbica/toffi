#pragma once

#include <atomic>
#include <thread>

class Timer {
private:
    std::atomic<float>  m_time{ 0.0 };
    std::atomic<bool> m_running{ false };

public:
    Timer(float time);

    void Start();

    void setTime(float time);

    bool isRunning();
};

