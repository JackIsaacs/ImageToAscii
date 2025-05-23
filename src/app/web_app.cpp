#include "web_app.h"

#include <filesystem>
#include <fstream>

#include "../tasks/image_to_ascii_task.h"
#include "../tasks/load_image_task.h"

void WebApp::Start()
{
    m_server.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_content(R"(
            <form method="POST" enctype="multipart/form-data" action="/upload">
                <input type="file" name="image" />
                <input type="submit" />
            </form>
        )", "text/html");
    });
    
    m_server.Post("/upload", [&](const httplib::Request& req, httplib::Response& res) {
        const httplib::MultipartFormData& file = req.get_file_value("image");
        HandleUpload(file.content, res);
    });

    m_threadHandle = std::thread(&WebApp::ServerThread, this);
}

void WebApp::Shutdown()
{
    m_server.stop();
    m_threadHandle.join();
    std::cout << "Server stopped" << "\n";
}

void WebApp::ServerThread()
{
    m_server.listen("localhost", 8080);
}

void WebApp::HandleUpload(const std::string& content, httplib::Response& res)
{
   
    const std::wstring filename = L"upload.jpg";
    std::ofstream out(filename, std::ios::binary);
    out.write(content.data(), static_cast<std::streamsize>(content.size()));
    out.close();

    LoadImageTask loadImageTask(filename);
    loadImageTask.Start();
    
    if (loadImageTask.WaitForThread() == TASK_ERROR)
    {
        res.set_content("loadImageTask error", "text/plain");
        return;
    }
    
    ImageToAsciiTask imageToAsciiTask(loadImageTask.GetImageInfo().w, loadImageTask.GetImageInfo().pixels, 1.0f);
    imageToAsciiTask.Start();
    
    if (imageToAsciiTask.WaitForThread() == TASK_ERROR)
    {
        res.set_content("imageToAsciiTask error", "text/plain");
        return;
    }

    std::string html = R"(
    <html>
      <head>
        <style>
          body {
            background-color: #000;
            color: #0f0;
            font-family: monospace;
            font-size: 4px;
            white-space: pre;
          }
        </style>
      </head>
      <body>
        <pre>)" + imageToAsciiTask.GetOutputBuffer() + R"(</pre>
        <br>
        <br>
        <a href="/"><button type="button">Try another image!</button></a>
      </body>
    </html>
    )";
    
    res.set_content(html, "text/html");
}
