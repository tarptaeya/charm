#pragma once

#include "gl/Context.h"
#include "graphics/render_target/RenderTarget.h"
#include "ui/elements/Element.h"

namespace charm::ui {

class Canvas : public Element {
    RenderTarget& m_render_target;

public:
    Canvas(Context& context, RenderTarget& render_target);
    void draw() override;

    float get_min_width() const override;
    float get_min_height() const override;
};

}