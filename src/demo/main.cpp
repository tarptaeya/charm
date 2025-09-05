#include "FPSCounter.h"
#include "charm.h"
#include "game_objects/RootObject.h"
#include <iostream>

using namespace charm;

class Example : public charm::AppAdapter {
    Camera m_camera;
    RootObject m_object;
    RenderTarget m_render_target;
    int m_count = 0;

    ui::Label* m_fps_label;

public:
    Example(ui::Document& document)
        : charm::AppAdapter(document)
    {
        glfwSwapInterval(0);

        m_camera.set_projection(Matrix4f::perspective(M_PI / 3, 1.0, 0.1, 100));
        m_camera.set_view(Matrix4f::look_at(Vector3f(0, 0, 3), Vector3f(0, 0, 0), Vector3f(0, 1, 0)));

        m_fps_label = new ui::Label("");
        m_document.add(m_fps_label);
    }

    ~Example()
    {
        delete m_fps_label;
    }

    void update(double delta_time) override
    {
        gl::Context::bind(GL_FRAMEBUFFER, m_render_target.get_framebuffer());
        gl::Context::viewport(0, 0, m_render_target.get_width(), m_render_target.get_height());
        gl::Context::enable(GL_DEPTH_TEST);
        gl::Context::clear_color(0.1, 0.2, 0.3, 1.0);
        gl::Context::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_object.render(m_camera);

        gl::Context::reset_framebuffer(GL_FRAMEBUFFER);

        FPSCounter::get_instance().push(delta_time);
        m_fps_label->set_text("FPS: " + std::to_string((int)FPSCounter::get_instance().get()));
    }
};

int main()
{
    AppOptions options;
    options.window_width = 1024;
    options.window_height = 720;
    options.window_title = "Charmed Demo";
    options.font_texture_path = "res/charm/bitmap.png";
    options.font_metadata_path = "res/charm/font.txt";

    charmApp.initialize(options);

    return charmApp.exec<Example>();
}