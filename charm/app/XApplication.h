#pragma once

#include "XAppOptions.h"
#include "graphics/shaders/XShaderRegistry.h"
#include <iostream>

#define xApp XApplication::get_instance()
#define xShaderRegistry xApp->get_shader_registry()

class XWindow;
class XAppAdapter;

class XApplication {
    XWindow* m_window = nullptr;
    XAppAdapter* m_adapter = nullptr;
    XShaderRegistry m_shader_registry;
    static XApplication* s_instance;

    explicit XApplication(const XAppOptions&);

public:
    ~XApplication();
    XApplication(const XApplication&) = delete;
    XApplication& operator=(const XApplication&) = delete;

    XShaderRegistry* get_shader_registry();

    template <typename T>
    static void create(const XAppOptions& options)
    {
        if (s_instance) {
            std::cerr << "[error] app instance already exists" << std::endl;
            std::exit(1);
        }

        s_instance = new XApplication(options);
        s_instance->m_adapter = new T;
    }

    template <typename T>
    static void create()
    {
        XAppOptions options;
        create<T>(options);
    }

    int exec();

    static XApplication* get_instance();
};
