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
        charm::Mat4 transform = charm::Mat4::identity();
        add_object<TestObject>(transform);
    }
}

void RootObject::update(double delta_time)
{
    for (const auto& object : m_objects) {
        object->update(delta_time);
    }

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

    static float angle = 0;
    angle += delta_time * 0.5;

    for (int i = 0; i < 10; ++i) {
        charm::Mat4 transform = charm::Mat4::identity();
        transform *= charm::Mat4::translation(positions[i][0], positions[i][1], positions[i][2]);
        transform *= charm::Mat4::rotation_y(angle + i * 1.7);
        transform *= charm::Mat4::scaling(0.1);
        dynamic_cast<TestObject*>(m_objects[i].get())->set_transform(transform);
    }
}

void RootObject::render(charm::Camera& camera)
{
    for (auto& object : m_objects) {
        object->render(camera);
    }
}
