#include "charm.h"
#include "testing.h"

using namespace charm;

void test_add()
{
    Mat4 a({ { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 },
        { 13, 14, 15, 16 } });

    a += a;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ASSERT_TRUE(a(i, j) == 2 * (i * 4 + j + 1));
        }
    }
}

void test_mul()
{
    Mat4 a = Mat4::identity();
    Mat4 b = Mat4::identity();
    a *= b;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ASSERT_TRUE(a(i, j) == b(i, j));
        }
    }

    a.inverse();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ASSERT_TRUE(a(i, j) == b(i, j));
        }
    }

    Mat4 c({ { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 },
        { 13, 14, 15, 16 } });
    Mat4 d({ { 17, 18, 19, 20 },
        { 21, 22, 23, 24 },
        { 25, 26, 27, 28 },
        { 29, 30, 31, 32 } });
    Mat4 cd({ { 250, 260, 270, 280 },
        { 618, 644, 670, 696 },
        { 986, 1028, 1070, 1112 },
        { 1354, 1412, 1470, 1528 } });

    Mat4 r = c * d;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ASSERT_TRUE(r(i, j) == cd(i, j));
        }
    }
}

void test_inverse()
{
    Mat4 a({ { 1, 2, 3, 4 },
        { 0, 1, 2, 3 },
        { 0, 0, 1, 2 },
        { 0, 0, 0, 1 } });

    a *= a.inversed();

    Mat4 id = Mat4::identity();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ASSERT_TRUE(a(i, j) == id(i, j));
        }
    }
}

int main()
{
    test_add();
    test_mul();
    test_inverse();
}