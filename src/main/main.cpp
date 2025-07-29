#include "charm.h"

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
    charm::AppOptions options;
    options.window_title = "Charmed Demo";

    charm::Application::create(options);
    charm::Application::set_adapter(new GameAdapter);
    return charmApp->exec();
}