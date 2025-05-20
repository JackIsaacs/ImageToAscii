#include "threaded_task.h"

using Clock = std::chrono::steady_clock;

void ThreadedTask::Start()
{
    m_finished = false;
    m_startTime = Clock::now();
    m_threadHandle = std::thread(&ThreadedTask::Task, this);
}

bool ThreadedTask::CanJoin()
{
    if (m_finished)
    {
        m_threadHandle.join();
        return true;
    }

    return false;
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
}
