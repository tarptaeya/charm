#include "charm.h"
#include "testing.h"

using namespace charm;

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

int main()
{
    test_matmul_1();
    test_matmul_2();
    test_matmul_3();
    test_matmul_4();
}