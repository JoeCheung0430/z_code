#pragma once

#include <ostream>
#include <thread>
#include <atomic>
#include <functional>

class EVTimer
{
public:
    EVTimer();
    EVTimer(int repeat);
    ~EVTimer();

    template <typename F, typename... Args>
    void start_timer(int millisecond, F&& func, Args&&... args);
    void stop_timer();

private:
    std::thread m_thread;
    std::atomic<bool> m_active;
    std::function<void()> m_func;
    int m_period;  // millisecond
    int m_repeat;
};