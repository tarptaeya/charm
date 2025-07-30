#include "charm.h"
#include <iostream>
#include <unistd.h>

class GameAdapter : public charm::AppAdapter {
public:
    GameAdapter()
    {
        charmApp->get_shader_registry()->add_shader(GL_VERTEX_SHADER, "assets/basic.vertex.glsl");
    }

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

    charm::Application::create<GameAdapter>(options);
    return charmApp->exec();
}