#include "charm.h"
#include <iostream>
#include <unistd.h>

using namespace charm;

class GameAdapter : public charm::AppAdapter {

public:
    GameAdapter()
    {
        charmShaderRegistry->add_shader(GL_VERTEX_SHADER, "assets/basic.vertex.glsl");
        charmShaderRegistry->add_shader(GL_FRAGMENT_SHADER, "assets/basic.fragment.glsl");

        ShaderProgram program(charmShaderRegistry->get_shader("assets/basic.vertex.glsl"), charmShaderRegistry->get_shader("assets/basic.fragment.glsl"));
        program.use();
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
    AppOptions options;
    options.window_title = "Charmed Demo";

    Application::create<GameAdapter>(options);
    return charmApp->exec();
}