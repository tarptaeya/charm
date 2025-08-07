#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "AppOptions.h"
#include "Registry.h"
#include "graphics/geometry/Geometry.h"
#include "graphics/material/Material.h"
#include "graphics/shaders/Shader.h"
#include <iostream>

#define charmApp charm::Application::get_instance()
#define charmWindow charmApp->get_window()
#define charmShaders charmApp->get_shader_registry()
#define charmMaterials charmApp->get_material_registry()
#define charmGeometries charmApp->get_geometry_registry()

namespace charm {

class Window;
class AbstractGameLoop;

class Application {
    GLFWwindow* m_window = nullptr;
    AbstractGameLoop* m_game_loop = nullptr;
    Registry<Shader> m_shaders;
    Registry<Material> m_materials;
    Registry<Geometry> m_geometries;
    static Application* s_instance;

    explicit Application(const AppOptions&);

    friend class Input;

public:
    ~Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    GLFWwindow* get_window() const;
    Registry<Shader>& get_shader_registry();
    Registry<Material>& get_material_registry();
    Registry<Geometry>& get_geometry_registry();

    template <typename T>
    static void create(const AppOptions& options)
    {
        if (s_instance) {
            std::cerr << "[error] app instance already exists" << std::endl;
            std::exit(1);
        }

        s_instance = new Application(options);
        s_instance->m_game_loop = new T;
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