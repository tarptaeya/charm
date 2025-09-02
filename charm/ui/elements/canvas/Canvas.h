#pragma once

#include "gl/Context.h"
#include "ui/elements/Element.h"

namespace charm::ui {

class Canvas : public Element {
    gl::Texture& m_texture;

public:
    Canvas(Context& context, gl::Texture& texture);
    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;
};

}