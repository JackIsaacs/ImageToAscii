#pragma once
#include "../../external/httplib.h"

class WebApp
{
public:
    void Start();
    void Shutdown();

private:
    void ServerThread();
    void HandleUpload(const std::string& content, httplib::Response& res);

    std::thread m_threadHandle;
    std::mutex m_mutex;
    
    httplib::Server m_server;
};
