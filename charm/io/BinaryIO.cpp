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

}