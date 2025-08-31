#pragma once

#define GLFW_INCLUDE_NONE
#include "AppOptions.h"
#include "gl/Context.h"
#include "ui/Document.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <functional>
#include <iostream>

#define charmApp charm::Application::get_instance()
#define charmWindow charmApp.get_window()

namespace charm {

class Window;
class AppAdapter;
class Font;

class Application {
    friend class Input;

    GLFWwindow* m_window = nullptr;
    GLFWcursor* m_cursor = nullptr;
    int m_width = 0;
    int m_height = 0;
    std::vector<std::pair<int, std::function<void()>>> m_functions_to_execute_on_frame_end;
    std::unique_ptr<Font> m_font = nullptr;
    gl::Program m_ui_program;

    Application() = default;

public:
    ~Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void initialize(const AppOptions&);

    GLFWwindow* get_window() const;
    int get_width() const;
    int get_height() const;

    template <class T, typename... Args>
    int exec(Args&... args)
    {
        static_assert(std::is_base_of<AppAdapter, T>::value, "T should be a subclass of Adapter");

        ui::Document document;

        T adapter(document, std::forward<Args>(args)...);
        double prev_time = glfwGetTime();
        while (!glfwWindowShouldClose(m_window)) {
            double curr_time = glfwGetTime();
            double delta_time = curr_time - prev_time;
            prev_time = curr_time;

            gl::Context::unbind_framebuffer(GL_FRAMEBUFFER);
            adapter.update(delta_time);

            draw_document(document);

            std::sort(m_functions_to_execute_on_frame_end.begin(), m_functions_to_execute_on_frame_end.end(), [](const auto& a, const auto& b) {
                return a.first < b.first;
            });
            for (const auto& [_priority, function] : m_functions_to_execute_on_frame_end) {
                function();
            }
            m_functions_to_execute_on_frame_end.clear();

            glfwPollEvents();
            glfwSwapBuffers(m_window);
        }

        return 0;
    }

    static Application& get_instance();

    void set_cursor(int shape);
    void execute_on_frame_end(int priority, const std::function<void()>&);

    Font& get_font();
    void set_font(const std::string& texture_path, const std::string& metadata_path);

    void draw_document(ui::Document& document);
};

}