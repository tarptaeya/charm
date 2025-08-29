#include "DemoAdapter.h"
#include "FPSCounter.h"
#include "ScreenGeometry.h"

using namespace charm;

int count = 0;
int swap_interval = 0;

DemoAdapter::DemoAdapter()
{
    glfwSwapInterval(swap_interval);

    m_camera.set_projection(Matrix4f::perspective(M_PI / 3, 1024.0 / 720.0, 0.1, 100));
    m_camera.set_view(Matrix4f::look_at(Vector3f(0, 0, 3), Vector3f(0, 0, 0), Vector3f(0, 1, 0)));

    m_main_framebuffer = FramebufferBuilder().create(1024, 720);
    m_hud_framebuffer = FramebufferBuilder().create(1024, 720);

    m_document = charm::ui::Document();

    auto& topbox = m_document.add<ui::PaddedContainer>(4).add<ui::HBoxContainer>();
    auto& fps_label = topbox.add<ui::Label>("");
    fps_label.set_id("fps_label");
    topbox.add<ui::HBoxContainer>();
    auto& toggle_swap_button = topbox.add<ui::Button>("Toggle Swap Interval");
    toggle_swap_button.set_is_height_expandable(true);
    toggle_swap_button.set_on_click_handler([] {
        swap_interval = 1 - swap_interval;
        glfwSwapInterval(swap_interval);
    });

    auto& hbox = m_document.add<ui::PaddedContainer>(4).add<ui::HBoxContainer>();
    auto& counter_label = hbox.add<ui::Label>("Current count: 0");
    hbox.add<ui::HBoxContainer>();

    auto& nested_hbox = hbox.add<ui::HBoxContainer>();
    nested_hbox.set_is_width_expandable(false);
    auto& increment_button = nested_hbox.add<ui::PaddedContainer>(0).add<ui::Button>("Increment (+)");
    increment_button.set_on_click_handler([&increment_button, &counter_label] {
        ++count;
        counter_label.set_text("Current count: " + std::to_string(count));
    });

    auto& decrement_button = nested_hbox.add<ui::PaddedContainer>(4, 0, 0, 0).add<ui::Button>("Decrement (-)");
    decrement_button.set_on_click_handler([&decrement_button, &counter_label] {
        --count;
        counter_label.set_text("Current count: " + std::to_string(count));
    });
}

DemoAdapter::~DemoAdapter()
{
}

void DemoAdapter::update(double delta_time)
{
    m_main_framebuffer.bind();
    update_main_framebuffer(delta_time);

    m_hud_framebuffer.bind();
    update_hud_framebuffer(delta_time);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, charmApp.get_width(), charmApp.get_height());
    update_screen_framebuffer(delta_time);
}

void DemoAdapter::update_main_framebuffer(double delta_time)
{
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static Vector3f position(0, 0, 3);
    Vector3f front(0, 0, -1);

    float speed = 1.5 * delta_time;
    if (glfwGetKey(charmWindow, GLFW_KEY_W) == GLFW_PRESS) {
        position[2] -= speed;
        m_camera.set_view(Matrix4f::look_at(position, position + front, Vector3f(0, 1, 0)));
    } else if (glfwGetKey(charmWindow, GLFW_KEY_S) == GLFW_PRESS) {
        position[2] += speed;
        m_camera.set_view(Matrix4f::look_at(position, position + front, Vector3f(0, 1, 0)));
    } else if (glfwGetKey(charmWindow, GLFW_KEY_A) == GLFW_PRESS) {
        position[0] -= speed;
        m_camera.set_view(Matrix4f::look_at(position, position + front, Vector3f(0, 1, 0)));
    } else if (glfwGetKey(charmWindow, GLFW_KEY_D) == GLFW_PRESS) {
        position[0] += speed;
        m_camera.set_view(Matrix4f::look_at(position, position + front, Vector3f(0, 1, 0)));
    }

    m_root_object.update(delta_time);
    m_root_object.render(m_camera);
}

void DemoAdapter::update_hud_framebuffer(double delta_time)
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.78, 0.80, 0.82, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    blit_framebuffer_to_screen(m_main_framebuffer.get_gl_color_texture());

    float width = m_hud_framebuffer.get_width();
    float height = m_hud_framebuffer.get_height();

    charmShaders.get("ui").use();
    charmShaders.get("ui").set_uniform("u_font_texture", 1);
    charmShaders.get("ui").set_uniform("u_projection",
        Matrix4f({
            // clang-format off
                2.f / charmApp.get_width(), 0,                            0, 0,
                0,                          -2.f / charmApp.get_height(), 0, 0,
                0,                          0,                            1, 0,
                -1,                         1,                            0, 1,
            // clang-format on
        }));

    auto fps_label = m_document.get_element_by_id<ui::Label>("fps_label");
    FPSCounter::get_instance().push(delta_time);
    fps_label->set_text("Frames per second: " + std::to_string((int)FPSCounter::get_instance().get()));

    m_document.draw(charmApp.get_width() / 4, charmApp.get_height() - 22 - 100, charmApp.get_width() / 2, 100);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void DemoAdapter::update_screen_framebuffer(double delta_time)
{
    glClearColor(0.3, 0.5, 0.7, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    blit_framebuffer_to_screen(m_hud_framebuffer.get_gl_color_texture());
}

void DemoAdapter::blit_framebuffer_to_screen(unsigned int texture_handle)
{
    charmShaders.get("screen").use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_handle);
    ScreenGeometry::get_instance().get_geometry().draw();
}