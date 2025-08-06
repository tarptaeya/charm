#pragma once

#include "XAppOptions.h"
#include "XRegistry.h"
#include "graphics/geometry/XGeometry.h"
#include "graphics/material/XMaterial.h"
#include "graphics/shaders/XShader.h"
#include <iostream>

#define xApp XApplication::get_instance()
#define xShaders xApp->get_shader_registry()
#define xMaterials xApp->get_material_registry()
#define xGeometries xApp->get_geometry_registry()

class XWindow;
class XAppAdapter;

class XApplication {
    XWindow* m_window = nullptr;
    XAppAdapter* m_adapter = nullptr;
    XRegistry<XShader> m_shaders;
    XRegistry<XMaterial> m_materials;
    XRegistry<XGeometry> m_geometries;
    static XApplication* s_instance;

    explicit XApplication(const XAppOptions&);

    friend class XInput;

public:
    ~XApplication();
    XApplication(const XApplication&) = delete;
    XApplication& operator=(const XApplication&) = delete;

    XRegistry<XShader>& get_shader_registry();
    XRegistry<XMaterial>& get_material_registry();
    XRegistry<XGeometry>& get_geometry_registry();

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
