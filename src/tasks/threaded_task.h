#pragma once

#include <mutex>
#include <thread>

#define TASK_OK 0
#define TASK_ERROR 1

class ThreadedTask
{
public:
    ThreadedTask() = default;
    virtual ~ThreadedTask() = default;
    
    void Start();
    int WaitForThread();
    double GetDuration() const;

protected:
    virtual void Task();

    std::thread m_threadHandle;
    std::mutex m_mutex;

    std::chrono::time_point<std::chrono::steady_clock> m_startTime;
    double m_duration = 0;

    std::condition_variable m_cv;
    bool m_finished = false;
    int m_exitCode = TASK_OK;
};
