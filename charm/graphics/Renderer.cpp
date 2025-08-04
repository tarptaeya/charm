#include "Renderer.h"
#include "ecs/components/MeshRendererComponent.h"
#include "math/Matrix4f.h"

namespace charm {

void Renderer::render(Entity& entity)
{
    MeshRendererComponent* mesh_renderer_component = entity.get_component<MeshRendererComponent>();
    if (!mesh_renderer_component)
        return;

    Geometry& geometry = mesh_renderer_component->get_geometry();
    ShaderProgram& program = mesh_renderer_component->get_material().get_shader_program();

    program.use();
    Matrix4f model = Matrix4f::identity();
    Matrix4f view = Matrix4f::identity();
    Matrix4f projection = Matrix4f::identity();

    program.set_uniform("u_model", model);
    program.set_uniform("u_view", view);
    program.set_uniform("u_projection", projection);

    glBindVertexArray(geometry.get_vertex_array());
    glDrawElements(GL_TRIANGLES, geometry.get_count(), GL_UNSIGNED_INT, nullptr);
}

}