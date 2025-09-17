#include "BinaryIO.h"
#include <arpa/inet.h>
#include <cstring>

namespace charm {

int BinaryIO::read_int(std::ifstream& f)
{
    static_assert(sizeof(int) == 4);

    int data;
    f.read(reinterpret_cast<char*>(&data), sizeof(data));
    data = ntohl(data);
    return data;
}

unsigned int BinaryIO::read_unsigned_int(std::ifstream& f)
{
    static_assert(sizeof(unsigned int) == 4);

    unsigned int data;
    f.read(reinterpret_cast<char*>(&data), sizeof(data));
    data = ntohl(data);
    return data;
}

float BinaryIO::read_float(std::ifstream& f)
{
    static_assert(sizeof(float) == 4);

    uint32_t data;
    f.read(reinterpret_cast<char*>(&data), sizeof(data));
    data = ntohl(data);

    float result;
    std::memcpy(&result, &data, sizeof(data));
    return result;
}

std::string BinaryIO::read_string(std::ifstream& f)
{
    uint32_t len = read_unsigned_int(f);
    char* data = new char[len];
    f.read(data, sizeof(char) * len);
    std::string ans;
    for (int i = 0; i < len; ++i) {
        ans += data[i];
    }
    delete[] data;
    return ans;
}

Mat4 BinaryIO::read_mat4(std::ifstream& f)
{
    Mat4 ans;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ans(i, j) = read_float(f);
        }
    }

    return ans;
}

void BinaryIO::write(std::ofstream& f, int value)
{
    static_assert(sizeof(int) == 4);

    int data = htonl(value);
    f.write(reinterpret_cast<char*>(&data), sizeof(data));
}

void BinaryIO::write(std::ofstream& f, unsigned int value)
{
    static_assert(sizeof(unsigned int) == 4);

    uint32_t data = htonl(value);
    f.write(reinterpret_cast<char*>(&data), sizeof(data));
}

void BinaryIO::write(std::ofstream& f, float value)
{
    static_assert(sizeof(float) == 4);

    uint32_t data;
    std::memcpy(&data, &value, sizeof(float));
    data = htonl(data);
    f.write(reinterpret_cast<char*>(&data), sizeof(data));
}

void BinaryIO::write(std::ofstream& f, const std::string& text)
{
    write(f, (uint32_t)text.length());
    f.write(reinterpret_cast<const char*>(text.data()), text.length() * sizeof(char));
}

void BinaryIO::write(std::ofstream& f, const Mat4& mat)
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            write(f, mat(i, j));
        }
    }
}

}