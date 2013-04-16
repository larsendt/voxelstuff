#pragma once

#include "vertex.h"

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

typedef struct vertexbuffer_t {
    GLuint vbo_handle;
    GLuint vao_handle;
    GLenum mode;
    int vx_count;
} vertexbuffer_t;

vertexbuffer_t vbo_new(GLenum mode, vertex *vertices, unsigned int count);
void vbo_free(vertexbuffer_t *buf);
void vbo_draw(vertexbuffer_t *buf);


