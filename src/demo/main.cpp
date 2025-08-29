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
    options.font_texture_path = "res/charm/bitmap.png";
    options.font_metadata_path = "res/charm/font.txt";

    charmApp.initialize(options);

    return charmApp.exec<Example>();
}