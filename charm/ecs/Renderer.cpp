#include "Renderer.h"
#include "components/MeshRendererComponent.h"
#include "components/TransformComponent.h"
#include "math/Matrix4f.h"

namespace charm {

void Renderer::render(Entity& entity, Camera& camera)
{
    MeshRendererComponent* mesh_renderer_component = entity.get_component<MeshRendererComponent>();
    if (!mesh_renderer_component)
        return;

    TransformComponent* transform_component = entity.get_component<TransformComponent>();
    Geometry& geometry = mesh_renderer_component->get_geometry();
    Shader& shader = mesh_renderer_component->get_shader();

    shader.use();

    shader.set_uniform("u_model", transform_component->get_transform());
    shader.set_uniform("u_view", camera.get_view());
    shader.set_uniform("u_projection", camera.get_projection());

    geometry.draw();
}

}