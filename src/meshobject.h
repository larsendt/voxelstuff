#pragma once

#include "vertexbuffer.h"
#include "shader.h"

class MeshObject
{
    public:
        MeshObject(Shader *shader, VertexBuffer *vbo);

        void draw();

        Shader *shader;
        VertexBuffer *vbo;
};
