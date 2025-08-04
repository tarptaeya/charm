#pragma once

/**
 * This class represents a 4x4 matrix of floats. The
 * matrix works like a row major matrix, but is stored
 * internally in a column major order.
 */
class XMatrix4f {
    float m_data[16] = { 0 };

public:
    XMatrix4f() = default;
    /**
     * Constructs XMatrix4f from column major float[16] array
     *
     * @param data float[16] array in column major order
     */
    XMatrix4f(const float (&)[16]);
    ~XMatrix4f() = default;

    XMatrix4f(const XMatrix4f&) = default;
    XMatrix4f& operator=(const XMatrix4f&) = default;

    XMatrix4f(XMatrix4f&&) = default;
    XMatrix4f& operator=(XMatrix4f&&) = default;

    /**
     * Returns the matrix data in column major order.
     */
    const float* get_data() const;

    XMatrix4f& operator+=(const XMatrix4f&);
    XMatrix4f& operator-=(const XMatrix4f&);
    XMatrix4f& operator*=(const XMatrix4f&);
    XMatrix4f& operator*=(float);
    XMatrix4f& operator/=(float);

    friend XMatrix4f operator+(const XMatrix4f&, const XMatrix4f&);
    friend XMatrix4f operator-(const XMatrix4f&, const XMatrix4f&);
    friend XMatrix4f operator*(const XMatrix4f&, const XMatrix4f&);
    friend XMatrix4f operator*(float, const XMatrix4f&);
    friend XMatrix4f operator*(const XMatrix4f&, float);
    friend XMatrix4f operator/(float, const XMatrix4f&);
    friend XMatrix4f operator/(const XMatrix4f&, float);

    /**
     * Calculates matrix inverse in-place.
     */
    XMatrix4f& inverse();

    static XMatrix4f identity();
    static XMatrix4f scaling(float);
    static XMatrix4f scaling(float, float, float);

    static XMatrix4f rotation_x(float theta);
    static XMatrix4f rotation_y(float theta);
    static XMatrix4f rotation_z(float theta);

    static XMatrix4f translation(float, float, float);

    /**
     * Returns symmetric perspective projection matrix.
     *
     * @param fov vertical field of view in radians
     * @param aspect_ratio width / height of image plane
     * @param near
     * @param far
     */
    static XMatrix4f perspective(float fov, float aspect_ratio, float near, float far);
};
