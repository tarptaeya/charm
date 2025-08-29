#include "charm.h"
#include <iostream>

using namespace charm;

class Example : public charm::AppAdapter {
public:
    Example(ui::Document& document)
        : charm::AppAdapter(document)
    {
        auto& hbox1 = m_document.add<ui::HBoxContainer>();
        hbox1.add<ui::Label>("Dear diary,");
        hbox1.add<ui::HBoxContainer>();
        hbox1.add<ui::Label>("Aug 28, 2025");

        auto& hbox2 = m_document.add<ui::HBoxContainer>();
        hbox2.add<ui::Label>("I have started implementing a UI system for my graphics engine.");
    }

    void update(double delta_time) override
    {
    }
};

int main()
{
    AppOptions options;
    options.window_width = 1024;
    options.window_height = 720;
    options.window_title = "Charmed Demo";

    charmApp.initialize(options);
    charmApp.set_font("res/charm/bitmap.png", "res/charm/font.txt");

    charmShaders.add("basic", Shader(FileIO::read_text("res/demo/basic.vertex.glsl"), FileIO::read_text("res/demo/basic.fragment.glsl")));
    charmShaders.add("ui", Shader(FileIO::read_text("res/charm/ui.vertex.glsl"), FileIO::read_text("res/charm/ui.fragment.glsl")));
    charmShaders.add("screen", Shader(FileIO::read_text("res/demo/screen.vertex.glsl"), FileIO::read_text("res/demo/screen.fragment.glsl")));
    charmShaders.add("font-test", Shader(FileIO::read_text("res/demo/font-test.vertex.glsl"), FileIO::read_text("res/demo/font-test.fragment.glsl")));
    charmGeometries.add("box", Geometry::box());

    return charmApp.exec<Example>();
}