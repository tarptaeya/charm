#include "RootObject.h"

RootObject::RootObject()
{
    float positions[10][3] = {
        { 0, 0, 0 },
        { 2, 5, -15 },
        { -1.5, -2.2, -2.5 },
        { -3.8, -2.0, -12.3 },
        { 2.4, -0.4, -3.5 },
        { -1.7, 3.0, -7.5 },
        { 1.3, -2.0, -2.5 },
        { 1.5, 2.0, -2.5 },
        { 1.5, 0.2, -1.5 },
        { -1.3, 1.0, -1.5 }
    };

    for (int i = 0; i < 10; ++i) {
        Matrix4f transform = Matrix4f::identity();
        transform *= Matrix4f::translation(positions[i][0], positions[i][1], positions[i][2]);
        transform *= Matrix4f::rotation_x(i * 20) * Matrix4f::rotation_y(i * 10) * Matrix4f::rotation_z(i * 30);
        transform *= Matrix4f::scaling(0.0075);
        add_object<TestObject>(transform);
    }
}

void RootObject::render(charm::Camera& camera)
{
    for (auto& object : m_objects) {
        object->render(camera);
    }
}
