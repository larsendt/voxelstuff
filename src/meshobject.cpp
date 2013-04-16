#include "meshobject.h"

#include <GL/gl.h>

MeshObject::MeshObject(Shader *shader, VertexBuffer *vbo)
{
    this->shader = shader;
    this->vbo = vbo;
}

void MeshObject::draw()
{
    glUseProgram(shader->handle);
    vbo->draw();
    glUseProgram(0);
}
