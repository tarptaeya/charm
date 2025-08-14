#pragma once

#include "misc/Rect.h"

namespace charm {

class IElement {
public:
    virtual ~IElement() { }

    virtual void update(double delta_time) = 0;
    virtual void render() = 0;
    virtual Rect get_rect(int parent_width, int parent_height) = 0;
};

}