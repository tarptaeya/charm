#pragma once

namespace charm {

/**
 * This class represents a 4x4 matrix of floats. The
 * matrix works like a row major matrix, but is stored
 * internally in a column major order.
 */
class Matrix4f {
    float m_data[16] = { 0 };

public:
    Matrix4f() = default;
    /**
     * Constructs Matrix4f from column major float[16] array
     *
     * @param data float[16] array in column major order
     */
    Matrix4f(const float (&)[16]);
    ~Matrix4f() = default;

    Matrix4f(const Matrix4f&) = default;
    Matrix4f& operator=(const Matrix4f&) = default;

    Matrix4f(Matrix4f&&) = default;
    Matrix4f& operator=(Matrix4f&&) = default;

    /**
     * Returns the matrix data in column major order.
     */
    const float* get_data() const;

    Matrix4f& operator+=(const Matrix4f&);
    Matrix4f& operator-=(const Matrix4f&);
    Matrix4f& operator*=(const Matrix4f&);
    Matrix4f& operator*=(float);
    Matrix4f& operator/=(float);

    friend Matrix4f operator+(const Matrix4f&, const Matrix4f&);
    friend Matrix4f operator-(const Matrix4f&, const Matrix4f&);
    friend Matrix4f operator*(const Matrix4f&, const Matrix4f&);
    friend Matrix4f operator*(float, const Matrix4f&);
    friend Matrix4f operator*(const Matrix4f&, float);
    friend Matrix4f operator/(float, const Matrix4f&);
    friend Matrix4f operator/(const Matrix4f&, float);

    /**
     * Calculates matrix inverse in-place.
     */
    Matrix4f& inverse();

    static Matrix4f identity();
    static Matrix4f scaling(float);
    static Matrix4f scaling(float, float, float);

    static Matrix4f rotation_x(float theta);
    static Matrix4f rotation_y(float theta);
    static Matrix4f rotation_z(float theta);

    static Matrix4f translation(float, float, float);

    /**
     * Returns symmetric perspective projection matrix.
     *
     * @param fov vertical field of view in radians
     * @param aspect_ratio width / height of image plane
     * @param near
     * @param far
     */
    static Matrix4f perspective(float fov, float aspect_ratio, float near, float far);
};

}