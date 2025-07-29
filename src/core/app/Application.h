#pragma once

#include "AppOptions.h"

#define charmApp charm::Application::get_instance()

namespace charm {

class Window;

class Application {
    Window* m_window = nullptr;
    AppOptions m_app_options;
    static Application* s_instance;

    explicit Application(const AppOptions&);

public:
    ~Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    static void create(const AppOptions&);
    static void create();
    int exec();

    static Application* get_instance();
};

}