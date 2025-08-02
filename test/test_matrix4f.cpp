#include "charm.h"
#include "testing.h"

using namespace charm;

void test_basic_op()
{
    // clang-format off
    float data[] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16,
    };
    // clang-format on

    Matrix4f a(data);
    a *= 3;
    for (int i = 0; i < 16; ++i) {
        ASSERT_TRUE(a.get_data()[i] == data[i] * 3);
    }

    Matrix4f b(data);
    b *= 2.5f;
    for (int i = 0; i < 16; ++i) {
        ASSERT_TRUE(b.get_data()[i] == data[i] * 2.5f);
    }

    Matrix4f c = Matrix4f(data) * 2;
    Matrix4f d = Matrix4f(data) * 3;
    Matrix4f e = c + d;
    for (int i = 0; i < 16; ++i) {
        ASSERT_TRUE(e.get_data()[i] == data[i] * 5);
    }
}

void test_matmul_1()
{
    Matrix4f a = Matrix4f::identity();
    Matrix4f b = Matrix4f::identity();
    Matrix4f c = a * b;
    a *= b;
    for (int i = 0; i < 16; ++i) {
        ASSERT_TRUE(a.get_data()[i] == b.get_data()[i]);
        ASSERT_TRUE(c.get_data()[i] == a.get_data()[i]);
    }
}

void test_matmul_2()
{
    // clang-format off
    Matrix4f a({
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16,
    });
    // clang-format on

    float expected[16];
    for (int i = 0; i < 16; ++i) {
        expected[i] = a.get_data()[i];
    }

    Matrix4f b = Matrix4f::identity();
    Matrix4f c = a * b;
    a *= b;
    for (int i = 0; i < 16; ++i) {
        ASSERT_TRUE(a.get_data()[i] == expected[i]);
        ASSERT_TRUE(c.get_data()[i] == a.get_data()[i]);
    }
}

void test_matmul_3()
{
    // clang-format off
    Matrix4f a = Matrix4f::identity();
    Matrix4f b({
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16,
    });
    // clang-format on

    float expected[16];
    for (int i = 0; i < 16; ++i) {
        expected[i] = b.get_data()[i];
    }

    Matrix4f c = a * b;
    a *= b;
    for (int i = 0; i < 16; ++i) {
        ASSERT_TRUE(a.get_data()[i] == expected[i]);
        ASSERT_TRUE(c.get_data()[i] == a.get_data()[i]);
    }
}

void test_matmul_4()
{
    // clang-format off
    Matrix4f a({
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16,
    });
    Matrix4f b({
        17, 18, 19, 20,
        21, 22, 23, 24,
        25, 26, 27, 28,
        29, 30, 31, 32,
    });

    float expected[16] = {
        538, 612, 686, 760,
        650, 740, 830, 920,
        762, 868, 974, 1080,
        874, 996, 1118, 1240,
    };
    // clang-format on

    Matrix4f c = a * b;
    a *= b;
    for (int i = 0; i < 16; ++i) {
        ASSERT_TRUE(a.get_data()[i] == expected[i]);
        ASSERT_TRUE(c.get_data()[i] == a.get_data()[i]);
    }
}

void test_inverse()
{
    Matrix4f a = Matrix4f::identity();
    Matrix4f b = Matrix4f::identity();
    a.inverse();
    for (int i = 0; i < 16; ++i) {
        ASSERT_TRUE(a.get_data()[i] == b.get_data()[i]);
    }

    // clang-format off
    Matrix4f c({
        1, 3, 6, 11,
        12, 4, 7, 10,
        9, 2, 5, 8,
        13, 15, 14, 16
    });
    float expected[16] = {
        -2/9.0, -85/81.0, 107/81.0, 4/27.0,
        -2/3.0, -133/27.0, 149/27.0, 7/9.0,
        14/9.0, 991/81.0, -1136/81.0, -46/27.0,
        -5/9.0, -424/81.0, 488/81.0, 19/27.0
    };
    // clang-format on
    c.inverse();
    for (int i = 0; i < 16; ++i) {
        ASSERT_TRUE(c.get_data()[i] == expected[i]);
    }
}

int main()
{
    test_basic_op();
    test_matmul_1();
    test_matmul_2();
    test_matmul_3();
    test_matmul_4();
    test_inverse();
}