#include "RootObject.h"
#include "Ground.h"

constexpr int N = 4;

RootObject::RootObject()
{
    m_ground = std::make_unique<Ground>();

    for (int i = 0; i < N * N; ++i) {
        charm::Mat4 transform = charm::Mat4::identity();
        add_object<TestObject>(transform);
    }
}

void RootObject::update(double delta_time)
{
    for (const auto& object : m_objects) {
        object->update(delta_time);
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            charm::Mat4 transform = charm::Mat4::identity();
            transform *= charm::Mat4::translation(i * 2, 0, j * 2);
            transform *= charm::Mat4::scaling(1.0);
            dynamic_cast<TestObject*>(m_objects[i * 4 + j].get())->set_transform(transform);
        }
    }

    m_ground->update(delta_time);
}

void RootObject::render(charm::Camera& camera)
{
    for (auto& object : m_objects) {
        object->render(camera);
    }

    m_ground->render(camera);
}
