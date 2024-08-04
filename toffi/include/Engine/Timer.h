#pragma once

#include <atomic>
#include <thread>

class Timer {
private:
	float m_time;
	std::atomic<bool> m_running{false};
	std::atomic<bool> m_stop{false};
	std::thread m_thread;
	std::condition_variable m_cv;
	std::mutex m_mutex;

public:
    Timer(float time);
	~Timer();

    void Start();

    void setTime(float time);

    bool isRunning();
};

