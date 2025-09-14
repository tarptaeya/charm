#include "Paragraph.h"

namespace charm::ui {

namespace {
    struct Lexer {
        int index = 0;
        std::string text;

        Lexer(const std::string& text)
            : index(0)
            , text(text)
        {
        }

        bool has_next() const
        {
            return index < text.size();
        }

        std::string get_next_word()
        {
            if (std::isalpha(text[index])) {
                std::string result;
                while (index < text.size() && std::isalpha(text[index])) {
                    result += text[index++];
                }
                return result;
            } else {
                std::string result;
                result += text[index++];
                return result;
            }
        }
    };
}

Paragraph::Paragraph(const std::string& text)
    : Element()
    , m_text(text)
{
    set_is_width_expandable(true);
}

Paragraph::~Paragraph()
{
}

void Paragraph::draw()
{
    Element::draw();

    build_layout();

    auto& ui_context = Context::get_instance();

    int num_rows = m_layout.size();
    float ycurr = m_y + m_font_size;
    for (int i = 0; i < num_rows; ++i) {
        float xcurr = m_x;
        for (const auto& text : m_layout[i]) {
            for (char c : text) {
                auto chrect = Label::get_rect_for_char(c, m_font_size);
                Context::Rect rect(chrect.x + xcurr, chrect.y + ycurr, chrect.width, chrect.height);
                rect.set_color(m_style.text_color)
                    .set_active_texture(FONT_TEXTURE_UNIT)
                    .set_texcoords({ chrect.u1, chrect.v1 }, { chrect.u2, chrect.v2 })
                    .clip(m_clip_x, m_clip_y, m_clip_width, m_clip_height);
                ui_context.add_rect(rect);
                xcurr += chrect.advance;
            }
        }

        ycurr += m_font_size;
    }
}

float Paragraph::get_min_width() const
{
    return 100;
}

float Paragraph::get_min_height() const
{
    return (m_font_size + 1) * m_layout.size();
}

std::string Paragraph::get_text() const
{
    return m_text;
}

void Paragraph::set_text(const std::string& text)
{
    m_text = text;
}

int Paragraph::get_font_size() const
{
    return m_font_size;
}

void Paragraph::set_font_size(int size)
{
    m_font_size = size;
}

void Paragraph::build_layout()
{
    if (m_cached_layout_width == m_width) {
        return;
    }

    m_cached_layout_width = m_width;
    m_layout.clear();
    float x_curr = 0;
    float row_index = 0;
    auto add_word_to_row = [this](int index, const std::string& word) {
        while (m_layout.size() <= index) {
            m_layout.push_back(std::vector<std::string>());
        }
        m_layout[index].push_back(word);
    };

    Lexer lexer(m_text);
    while (lexer.has_next()) {
        auto word = lexer.get_next_word();
        float width = 0;
        for (char c : word) {
            auto rect = Label::get_rect_for_char(c, m_font_size);
            width += rect.advance;
        }
        if (x_curr + width <= m_width) {
            add_word_to_row(row_index, word);
            x_curr += width;
        } else if (word.size() == 1 && std::isspace(word[0])) {
            ++row_index;
            x_curr = width;
        } else {
            ++row_index;
            add_word_to_row(row_index, word);
            x_curr = width;
        }
    }
}

}