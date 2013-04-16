#pragma once

#include "vertex.h"

#include <GL/gl.h>

class VertexBuffer
{
    public:
        VertexBuffer(GLenum mode, vertex *vertices, unsigned int count);
        ~VertexBuffer();

        void draw();

        GLuint vbo_handle;
        GLuint vao_handle;
        GLenum mode;
        unsigned int vx_count;
};

