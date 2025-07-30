#pragma once

#include "AppOptions.h"
#include "graphics/shaders/ShaderRegistry.h"
#include <iostream>

#define charmApp charm::Application::get_instance()

namespace charm {

class Window;
class AppAdapter;

class Application {
    Window* m_window = nullptr;
    AppAdapter* m_adapter = nullptr;
    ShaderRegistry m_shader_registry;
    static Application* s_instance;

    explicit Application(const AppOptions&);

public:
    ~Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    ShaderRegistry* get_shader_registry();

    template <typename T>
    static void create(const AppOptions& options)
    {
        if (s_instance) {
            std::cerr << "[error] app instance already exists" << std::endl;
            std::exit(1);
        }

        s_instance = new Application(options);
        s_instance->m_adapter = new T;
    }

    template <typename T>
    static void create()
    {
        AppOptions options;
        create<T>(options);
    }

    int exec();

    static Application* get_instance();
};

}