#include "FPSCounter.h"
#include "charm.h"
#include "game_objects/RootObject.h"
#include <iostream>

using namespace charm;

void add_spacer(observer_ptr<ui::VBoxContainer>& container, ui::Panel* panel)
{
    container->add(panel->create<ui::Label>(" "));
}

class Example : public charm::AppAdapter {
    Camera m_camera;
    RootObject m_object;

    ui::Style m_style;
    std::unique_ptr<ui::Panel> m_panel = nullptr;
    observer_ptr<ui::Label> m_fps_counter = nullptr;

public:
    Example()
        : charm::AppAdapter()
    {
        glfwSwapInterval(0);

        m_style = ui::Style::standard(Color { 0.92, 0.2, 0.4 }, Color { 1, 1, 1 }, Color { 0.2, 0.3, 0.4 });
        m_panel = std::make_unique<ui::Panel>(m_style);

        m_camera.set_projection(Matrix4f::perspective(M_PI / 3, 1.0, 0.1, 100));
        m_camera.set_view(Matrix4f::look_at(Vector3f(0, 0, 3), Vector3f(0, 0, 0), Vector3f(0, 1, 0)));

        auto vbox = m_panel->create<ui::VBoxContainer>();
        auto scroll = m_panel->create<ui::ScrollArea>(vbox);

        auto main_container = m_panel->create<ui::VBoxContainer>();
        m_fps_counter = m_panel->create<ui::Label>("");
        main_container->add(m_fps_counter);
        add_spacer(main_container, m_panel.get());
        main_container->add(scroll);
        m_panel->set_root(main_container);

        auto input = m_panel->create<ui::TextInput>();
        vbox->add(input);

        for (int i = 0; i < 10; ++i) {
            auto label = m_panel->create<ui::Label>(std::to_string(i + 1) + ". Lorem Ipsum is simply dummy text of the printing and typesetting industry.");
            vbox->add(label);
        }

        add_spacer(vbox, m_panel.get());

        auto hbox = m_panel->create<ui::HBoxContainer>();
        for (int i = 0; i < 5; ++i) {
            auto button = m_panel->create<ui::Button>("Click Me");
            hbox->add(button);
        }

        add_spacer(vbox, m_panel.get());

        auto nested_scroll = m_panel->create<ui::ScrollArea>(hbox);
        nested_scroll->set_is_width_expandable(false).set_is_height_expandable(false);
        vbox->add(nested_scroll);

        add_spacer(vbox, m_panel.get());

        auto checkbox = m_panel->create<ui::Checkbox>("I am a checkbox!");
        vbox->add(checkbox);

        add_spacer(vbox, m_panel.get());

        auto button = m_panel->create<ui::Button>("Remove labels");
        button->set_on_click_handler([](InputEventMouseButton& event) {
            event.stop_propagation();
        });
        vbox->add(button);

        std::string text = R"(
Members of an inline namespace are treated as if they are members of the enclosing namespace in many situations (listed below). This property is transitive: if a namespace N contains an inline namespace M, which in turn contains an inline namespace O, then the members of O can be used as though they were members of M or N.
)";
        auto paragraph = m_panel->create<ui::Paragraph>(text);
        vbox->add(paragraph);
    }

    ~Example()
    {
    }

    void update(double delta_time) override
    {
        gl::Context::reset_framebuffer(GL_FRAMEBUFFER);
        gl::Context::viewport(0, 0, charmApp.get_width(), charmApp.get_height());
        gl::Context::clear_color(0.3, 0.1, 0.2, 1.0);
        gl::Context::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_object.render(m_camera);

        FPSCounter::get_instance().push(delta_time);
        m_fps_counter->set_text("FPS: " + std::to_string((int)FPSCounter::get_instance().get()));

        m_panel->update(delta_time);
        m_panel->draw(50, 50, 300, 400);
    }

    void on_char_callback(InputEventChar& event) override
    {
        m_panel->on_char_callback(event);
    }

    void on_key_callback(InputEventKey& event) override
    {
        m_panel->on_key_callback(event);
    }

    void on_cursor_position_callback(InputEventMouseMotion& event) override
    {
        m_panel->on_cursor_pos_callback(event);
    }

    void on_mouse_button_callback(InputEventMouseButton& event) override
    {
        m_panel->on_mouse_button_callback(event);
    }

    void on_scroll_callback(InputEventScroll& event) override
    {
        m_panel->on_scroll_callback(event);
    }
};

int main()
{
    AppOptions options;
    options.window_width = 800;
    options.window_height = 800;
    options.window_title = "Charmed Demo";
    options.font_texture_path = "res/charm/bitmap.png";
    options.font_metadata_path = "res/charm/font.txt";

    charmApp.initialize(options);

    Example example;
    return charmApp.exec(&example);
}