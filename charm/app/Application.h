#pragma once

#define GLFW_INCLUDE_NONE
#include "AppOptions.h"
#include "gl/Context.h"
#include "memory/observer_ptr.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <functional>
#include <iostream>

#define charmApp charm::Application::get_instance()

namespace charm {

class Window;
class AppAdapter;
class Font;

class Application {
    friend class Input;

    AppOptions m_options;
    GLFWwindow* m_window = nullptr;
    int m_prev_cursor_shape = 0;
    GLFWcursor* m_cursor = nullptr;
    int m_width = 0;
    int m_height = 0;
    std::vector<std::pair<int, std::function<void()>>> m_functions_to_execute_on_frame_end;

    observer_ptr<AppAdapter> m_adapter = nullptr;

    Application() = default;

public:
    ~Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void initialize(const AppOptions&);

    int get_width() const;
    int get_height() const;

    const AppOptions& get_options() const;

    int exec(AppAdapter*);

    static Application& get_instance();

    void set_cursor(int shape);
    void execute_on_frame_end(int priority, const std::function<void()>&);
};

}