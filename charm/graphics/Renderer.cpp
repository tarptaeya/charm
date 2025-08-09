#include "Renderer.h"
#include "ecs/components/MeshRendererComponent.h"
#include "ecs/components/TransformComponent.h"
#include "math/Matrix4f.h"

namespace charm {

void Renderer::render(Entity& entity, Camera& camera)
{
    MeshRendererComponent* mesh_renderer_component = entity.get_component<MeshRendererComponent>();
    if (!mesh_renderer_component)
        return;

    TransformComponent* transform_component = entity.get_component<TransformComponent>();
    Geometry& geometry = mesh_renderer_component->get_geometry();
    Material& material = mesh_renderer_component->get_material();

    material.use();

    material.set_uniform("u_model", transform_component->get_transform());
    material.set_uniform("u_view", camera.get_view());
    material.set_uniform("u_projection", camera.get_projection());

    geometry.draw();
}

}