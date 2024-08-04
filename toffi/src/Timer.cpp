#include "Engine/Timer.h"

Timer::Timer(float time) {
	m_time = time;
}

Timer::~Timer() {
	m_stop = true;
	if (m_thread.joinable()) {
		m_cv.notify_all();
		m_thread.join();
	}
}

void Timer::Start() {
	m_running = true;
	m_stop = false;

	if (m_thread.joinable()) {
		m_thread.join();
	}

	m_thread = std::thread([this]() {
		std::unique_lock<std::mutex> lock(m_mutex);
		if (m_cv.wait_for(lock, std::chrono::seconds(static_cast<int>(m_time)), [this]() {
			return m_stop.load();
		})) {
			return;
		}
		m_running = false;
	});
}

void Timer::setTime(float time) {
	m_time = time;
}

bool Timer::isRunning() {
	return m_running;
}
