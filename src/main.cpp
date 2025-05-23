
#include "app/web_app.h"

int main(int argc, char* argv[])
{
    WebApp app;
    app.Start();

    std::cout << "Server running. Go to localhost:8080. Press enter to close server" << "\n";
    std::cin.get();
    app.Shutdown();
    
    return 0;
}
