#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <cmath>

#include "app/AppAdapter.h"
#include "app/AppOptions.h"
#include "app/Application.h"
#include "camera/Camera.h"
#include "ch3db/ch3db.h"
#include "gl/Context.h"
#include "graphics/font/Font.h"
#include "graphics/font/FontMetadata.h"
#include "graphics/geometry/Geometry.h"
#include "graphics/render_target/RenderTarget.h"
#include "io/BinaryIO.h"
#include "io/FileIO.h"
#include "math/Matrix4f.h"
#include "math/Vector3f.h"
#include "misc/builder/FramebufferBuilder.h"
#include "misc/builder/TextureBuilder.h"
#include "misc/misc.h"
#include "ui/Context.h"
#include "ui/Document.h"
#include "ui/elements/Element.h"
#include "ui/elements/button/Button.h"
#include "ui/elements/canvas/Canvas.h"
#include "ui/elements/hboxcontainer/HBoxContainer.h"
#include "ui/elements/label/Label.h"
#include "ui/elements/paddedcontainer/PaddedContainer.h"
#include "ui/elements/vboxcontainer/VBoxContainer.h"

#define ON_ENTER_ELEMENT_PRIORITY 1000
#define ON_EXIT_ELEMENT_PRIORITY (ON_ENTER_ELEMENT_PRIORITY - 1)