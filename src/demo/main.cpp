#include "FPSCounter.h"
#include "charm.h"
#include "game_objects/RootObject.h"
#include <iostream>

using namespace charm;

class Example : public charm::AppAdapter {
    Camera m_camera;
    RootObject m_object;
    std::tuple<gl::Framebuffer, gl::Texture, gl::Texture> m_render_target;

public:
    Example(ui::Document& document)
        : charm::AppAdapter(document)
    {
        m_camera.set_projection(Matrix4f::perspective(M_PI / 3, 1.0, 0.1, 100));
        m_camera.set_view(Matrix4f::look_at(Vector3f(0, 0, 3), Vector3f(0, 0, 0), Vector3f(0, 1, 0)));

        m_document.add<ui::Label>("").set_id("fps_counter");

        auto& hbox1 = m_document.add<ui::HBoxContainer>();
        hbox1.add<ui::Label>("Dear diary,");
        hbox1.add<ui::HBoxContainer>();
        hbox1.add<ui::Label>("Aug 28, 2025");

        m_document.add<ui::Label>("I have started implementing a UI system for my graphics engine.");

        m_render_target = FramebufferBuilder().create(256, 256);
        auto& container = m_document.add<ui::HBoxContainer>().add<ui::PaddedContainer>(22);
        container.set_is_height_expandable(false);
        container.set_is_width_expandable(false);
        container.add<ui::Canvas>(std::get<1>(m_render_target));
    }

    void update(double delta_time) override
    {
        gl::Context::bind(GL_FRAMEBUFFER, std::get<0>(m_render_target));
        gl::Context::viewport(0, 0, 256, 256);
        gl::Context::enable(GL_DEPTH_TEST);
        gl::Context::clear_color(0.1, 0.2, 0.3, 1.0);
        gl::Context::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_object.render(m_camera);

        gl::Context::reset_framebuffer(GL_FRAMEBUFFER);

        FPSCounter::get_instance().push(delta_time);
        m_document.get_element_by_id<ui::Label>("fps_counter")->set_text("FPS: " + std::to_string((int)FPSCounter::get_instance().get()));
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