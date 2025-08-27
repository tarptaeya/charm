#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "AppOptions.h"
#include "Registry.h"
#include "graphics/geometry/Geometry.h"
#include "graphics/shaders/Shader.h"
#include <algorithm>
#include <functional>
#include <iostream>

#define charmApp charm::Application::get_instance()
#define charmWindow charmApp.get_window()
#define charmShaders charmApp.get_shader_registry()
#define charmGeometries charmApp.get_geometry_registry()

namespace charm {

class Window;
class AppAdapter;

class Application {
    friend class Input;

    GLFWwindow* m_window = nullptr;
    GLFWcursor* m_cursor = nullptr;
    int m_width = 0;
    int m_height = 0;
    Registry<Shader> m_shaders;
    Registry<Geometry> m_geometries;
    std::vector<std::pair<int, std::function<void()>>> m_functions_to_execute_on_frame_end;

    Application() = default;

public:
    ~Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void initialize(const AppOptions&);

    GLFWwindow* get_window() const;
    int get_width() const;
    int get_height() const;
    Registry<Shader>& get_shader_registry();
    Registry<Geometry>& get_geometry_registry();

    template <class T, typename... Args>
    int exec(Args&... args)
    {
        static_assert(std::is_base_of<AppAdapter, T>::value, "T should be a subclass of Adapter");

        T adapter(std::forward<Args>(args)...);
        double prev_time = glfwGetTime();
        while (!glfwWindowShouldClose(m_window)) {
            double curr_time = glfwGetTime();
            double delta_time = curr_time - prev_time;
            prev_time = curr_time;

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, m_width, m_height);
            adapter.update(delta_time);

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
};

}