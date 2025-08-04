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
    ShaderProgram& program = mesh_renderer_component->get_material().get_shader_program();

    program.use();

    program.set_uniform("u_model", transform_component->get_transformation_matrix());
    program.set_uniform("u_view", camera.get_view());
    program.set_uniform("u_projection", camera.get_projection());

    glBindVertexArray(geometry.get_vertex_array());
    glDrawElements(GL_TRIANGLES, geometry.get_count(), GL_UNSIGNED_INT, nullptr);
}

}