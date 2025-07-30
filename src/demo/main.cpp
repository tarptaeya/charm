#include "charm.h"
#include <iostream>
#include <unistd.h>

class GameAdapter : public charm::AppAdapter {
    charm::ShaderProgram m_program;

public:
    GameAdapter()
    {
        charmShaderRegistry->add_shader(GL_VERTEX_SHADER, "assets/basic.vertex.glsl");
        charmShaderRegistry->add_shader(GL_FRAGMENT_SHADER, "assets/basic.fragment.glsl");

        m_program = std::move(charm::ShaderProgram(charmShaderRegistry->get_shader("assets/basic.vertex.glsl"), charmShaderRegistry->get_shader("assets/basic.fragment.glsl")));
    }

    ~GameAdapter() override = default;

    void update(double delta_time) override
    {
        glClearColor(0.1, 0.2, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        m_program.use();
    }
};

int main()
{
    charm::AppOptions options;
    options.window_title = "Charmed Demo";

    charm::Application::create<GameAdapter>(options);
    return charmApp->exec();
}