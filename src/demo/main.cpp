#include "FPSCounter.h"
#include "charm.h"
#include <iostream>

using namespace charm;

class Example : public charm::AppAdapter {
    gl::Texture m_flower_texture;
    gl::Texture m_night_texture;
    gl::Texture m_beach_texture;

public:
    Example(ui::Document& document)
        : charm::AppAdapter(document)
    {
        m_document.add<ui::Label>("").set_id("fps_counter");

        auto& hbox1 = m_document.add<ui::HBoxContainer>();
        hbox1.add<ui::Label>("Dear diary,");
        hbox1.add<ui::HBoxContainer>();
        hbox1.add<ui::Label>("Aug 28, 2025");

        m_document.add<ui::Label>("I have started implementing a UI system for my graphics engine.");

        auto& hbox2 = m_document.add<ui::HBoxContainer>();

        m_flower_texture = TextureBuilder("res/demo/flower.jpg").set_texture_unit(GL_TEXTURE2).build();
        m_night_texture = TextureBuilder("res/demo/night.jpg").set_texture_unit(GL_TEXTURE2).build();
        m_beach_texture = TextureBuilder("res/demo/beach.jpg").set_texture_unit(GL_TEXTURE2).build();

        hbox2.add<ui::PaddedContainer>(12).add<ui::Canvas>(m_flower_texture);
        hbox2.add<ui::PaddedContainer>(0, 12, 12, 12).add<ui::Canvas>(m_night_texture);
        hbox2.add<ui::PaddedContainer>(0, 12, 12, 12).add<ui::Canvas>(m_beach_texture);

        auto& spacer = m_document.add<ui::HBoxContainer>();
    }

    void update(double delta_time) override
    {
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