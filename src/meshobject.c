#include "meshobject.h"

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

meshobject_t new_meshobject(shader_t shader, vertexbuffer_t vbo)
{
    meshobject_t mesh;
    mesh.shader = shader;
    mesh.vbo = vbo;
    return mesh;
}

void free_meshobject(meshobject_t *mesh)
{
    vbo_free(&mesh->vbo);
    free_shader(&mesh->shader);
}

void draw_meshobject(meshobject_t *mesh)
{
    glUseProgram(mesh->shader.handle);
    vbo_draw(&mesh->vbo);
    glUseProgram(0);
}
