#include "charm.h"
#include <iostream>
#include <unistd.h>

class GameAdapter : public charm::AppAdapter {
public:
    ~GameAdapter() override = default;

    void update(double delta_time) override
    {
        glClearColor(0.1, 0.2, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};

int main()
{
    char path[512];
    getcwd(path, sizeof(path));
    std::cout << path << std::endl;

    charm::AppOptions options;
    options.window_title = "Charmed Demo";

    GameAdapter adapter;
    charm::Application::create(options, adapter);
    return charmApp->exec();
}