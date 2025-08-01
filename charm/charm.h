#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <cmath>

#include "app/AppAdapter.h"
#include "app/AppOptions.h"
#include "app/Application.h"
#include "app/Window.h"

#include "ecs/Component.h"
#include "ecs/Entity.h"

#include "graphics/shaders/ShaderProgram.h"
#include "graphics/shaders/ShaderRegistry.h"

#include "io/FileIO.h"

#include "math/Matrix4f.h"