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

#include "ecs/components/MeshRendererComponent.h"
#include "ecs/components/TransformComponent.h"

#include "graphics/geometry/BoxGeometry.h"
#include "graphics/geometry/Geometry.h"

#include "graphics/material/Material.h"

#include "graphics/shaders/ShaderProgram.h"
#include "graphics/shaders/ShaderRegistry.h"

#include "graphics/textures/ImageData.h"
#include "graphics/textures/Texture2D.h"
#include "graphics/textures/Texture2DBuilder.h"

#include "graphics/Renderer.h"

#include "io/FileIO.h"
#include "io/ppm/PPMReader.h"

#include "math/Matrix4f.h"