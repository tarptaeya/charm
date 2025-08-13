#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "AppOptions.h"
#include "Registry.h"
#include "graphics/geometry/Geometry.h"
#include "graphics/shaders/Program.h"
#include "graphics/shaders/Shader.h"
#include <iostream>

#define charmApp charm::Application::get_instance()
#define charmWindow charmApp->get_window()
#define charmShaders charmApp->get_shader_registry()
#define charmShaderPrograms charmApp->get_program_registry()
#define charmGeometries charmApp->get_geometry_registry()

namespace charm {

class Window;
class IGameLoop;

class Application {
    friend class Input;

    GLFWwindow* m_window = nullptr;
    int m_width = 0;
    int m_height = 0;
    IGameLoop* m_game_loop = nullptr;
    Registry<Shader> m_shaders;
    Registry<Program> m_programs;
    Registry<Geometry> m_geometries;
    static Application* s_instance;

    explicit Application(const AppOptions&);

public:
    ~Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    GLFWwindow* get_window() const;
    int get_width() const;
    int get_height() const;
    Registry<Shader>& get_shader_registry();
    Registry<Program>& get_program_registry();
    Registry<Geometry>& get_geometry_registry();

    template <typename T>
    static void create(const AppOptions& options)
    {
        if (s_instance) {
            std::cerr << "[error] app instance already exists" << std::endl;
            std::exit(0);
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