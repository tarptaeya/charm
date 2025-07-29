#pragma once

#include "AppOptions.h"

#define charmApp charm::Application::get_instance()

namespace charm {

class Window;
class AppAdapter;

class Application {
    Window* m_window = nullptr;
    AppAdapter* m_adapter = nullptr;
    AppOptions m_app_options;
    static Application* s_instance;

    explicit Application(const AppOptions&);

public:
    ~Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    static void create(const AppOptions&);
    static void create();
    static void set_adapter(AppAdapter*);
    int exec();

    static Application* get_instance();
};

}