#pragma once

#include "math/Vec3.h"

namespace charm {

struct DirectionalLight {
    Vec3 direction = Vec3(0, 0, 0);
    Vec3 ambient = Vec3(0, 0, 0);
    Vec3 diffuse = Vec3(0, 0, 0);
    Vec3 specular = Vec3(0, 0, 0);
};

}
