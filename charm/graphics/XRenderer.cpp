#include "XRenderer.h"
#include "ecs/components/XMeshRendererComponent.h"
#include "ecs/components/XTransformComponent.h"
#include "math/XMatrix4f.h"

void XRenderer::render(XEntity& entity, XCamera& camera)
{
    XMeshRendererComponent* mesh_renderer_component = entity.get_component<XMeshRendererComponent>();
    if (!mesh_renderer_component)
        return;

    XTransformComponent* transform_component = entity.get_component<XTransformComponent>();
    XGeometry& geometry = mesh_renderer_component->get_geometry();
    XProgram& program = mesh_renderer_component->get_material().get_program();

    program.use();

    program.set_uniform("u_model", transform_component->get_transform());
    program.set_uniform("u_view", camera.get_view());
    program.set_uniform("u_projection", camera.get_projection());

    glBindVertexArray(geometry.get_vertex_array());
    glDrawElements(GL_TRIANGLES, geometry.get_count(), GL_UNSIGNED_INT, nullptr);
}
