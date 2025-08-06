#pragma once

#include <vector>

namespace charm {

class ImageData {
    int m_width;
    int m_height;
    std::vector<unsigned char> m_data;

public:
    explicit ImageData(int width, int height);
    int get_width() const;
    int get_height() const;
    std::vector<unsigned char>& get_data();
};

}