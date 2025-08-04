#pragma once

#include <vector>

class XImageData {
    int m_width;
    int m_height;
    std::vector<unsigned char> m_data;

public:
    explicit XImageData(int width, int height);
    int get_width() const;
    int get_height() const;
    std::vector<unsigned char>& get_data();
};
