#pragma once

#include "misc/misc.h"

namespace charm::ui {

struct Style {
    Color background_color = { 0 };
    Color text_color = { 0 };
    Color button_color = { 0 };
    Color button_active_color = { 0 };
    Color button_text_color = { 0 };
    Color checkbox_color = { 0 };
    Color checkbox_background_color = { 0 };
    Color checkbox_text_color = { 0 };
    Color scroll_handle_color = { 0 };
    Color scroll_handle_active_color = { 0 };
    Color input_outline_color = { 0 };
    Color input_background_color = { 0 };
    Color input_text_color = { 0 };

    static Style standard(Color accent_color, Color text_color, Color background_color)
    {
        Style style;
        style.text_color = style.input_text_color = style.input_outline_color = style.checkbox_text_color = text_color;
        style.button_color = style.checkbox_color = style.scroll_handle_color = accent_color;
        style.background_color = style.checkbox_background_color = background_color;
        style.button_active_color = style.scroll_handle_active_color = Color { accent_color.r * 1.2f, accent_color.g * 1.3f, accent_color.b * 1.4f };
        style.button_text_color = style.input_background_color = Color { 1, 1, 1 };

        if (style.input_background_color == style.text_color) {
            style.input_background_color = style.background_color;
        }
        return style;
    }
};

}