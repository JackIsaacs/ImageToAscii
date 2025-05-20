#pragma once

#include <mutex>
#include <thread>

class ThreadedTask
{
public:
    ThreadedTask() = default;
    virtual ~ThreadedTask() = default;
    
    void Start();
    bool CanJoin();
    double GetDuration() const;

protected:
    virtual void Task();

    std::thread m_threadHandle;
    std::mutex m_mutex;

    std::chrono::time_point<std::chrono::steady_clock> m_startTime;
    bool m_finished = false;
    double m_duration = 0;
};
