#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cmath>
#include <glad/gl.h>

#include "app/AppAdapter.h"
#include "app/AppOptions.h"
#include "app/Application.h"
#include "camera/Camera.h"
#include "ch3db/ch3db.h"
#include "ecs/Component.h"
#include "ecs/Entity.h"
#include "ecs/Renderer.h"
#include "ecs/components/MeshRendererComponent.h"
#include "ecs/components/TransformComponent.h"
#include "gl/Context.h"
#include "graphics/font/Font.h"
#include "graphics/font/FontMetadata.h"
#include "graphics/framebuffer/Framebuffer.h"
#include "graphics/framebuffer/FramebufferBuilder.h"
#include "graphics/geometry/Geometry.h"
#include "graphics/shaders/Shader.h"
#include "graphics/textures/Texture2D.h"
#include "graphics/textures/Texture2DBuilder.h"
#include "io/BinaryIO.h"
#include "io/FileIO.h"
#include "math/Matrix4f.h"
#include "math/Vector3f.h"
#include "misc/Rect.h"
#include "misc/misc.h"
#include "ui/Context.h"
#include "ui/Document.h"
#include "ui/elements/Element.h"
#include "ui/elements/button/Button.h"
#include "ui/elements/hboxcontainer/HBoxContainer.h"
#include "ui/elements/label/Label.h"
#include "ui/elements/paddedcontainer/PaddedContainer.h"

#define ON_ENTER_ELEMENT_PRIORITY 1000
#define ON_EXIT_ELEMENT_PRIORITY (ON_ENTER_ELEMENT_PRIORITY - 1)