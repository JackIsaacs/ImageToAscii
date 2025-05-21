#include "threaded_task.h"

using Clock = std::chrono::steady_clock;

void ThreadedTask::Start()
{
    m_finished = false;
    m_startTime = Clock::now();
    m_exitCode = TASK_OK;
    m_threadHandle = std::thread(&ThreadedTask::Task, this);
}

int ThreadedTask::WaitForThread()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock, [this]() { return m_finished; });
    
    if (m_threadHandle.joinable())
    {
        m_threadHandle.join();
    }

    return m_exitCode;
}

double ThreadedTask::GetDuration() const
{
    return m_duration;
}

void ThreadedTask::Task()
{
    std::chrono::duration<double> duration = Clock::now() - m_startTime;
    
    std::lock_guard<std::mutex> lock(m_mutex);
    m_duration = duration.count();
    m_finished = true;
    m_cv.notify_one();
}
