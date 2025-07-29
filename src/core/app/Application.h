#pragma once

#include "AppOptions.h"

#define charmApp charm::Application::get_instance()

namespace charm {

class Window;
class AppAdapter;

class Application {
    Window* m_window = nullptr;
    AppAdapter& m_adapter;
    static Application* s_instance;

    explicit Application(const AppOptions&, AppAdapter&);

public:
    ~Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    static void create(const AppOptions&, AppAdapter&);
    static void create(AppAdapter&);
    static void set_adapter(AppAdapter&);
    int exec();

    static Application* get_instance();
};

}