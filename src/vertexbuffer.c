#include "vertexbuffer.h"

vertexbuffer_t vbo_new(GLenum mode, vertex *vertices, unsigned int count)
{
    vertexbuffer_t buf;
    buf.mode = mode;
    buf.vx_count = count;

    glGenVertexArrays(1, &buf.vao_handle);
    glBindVertexArray(buf.vao_handle);

    glGenBuffers(1, &buf.vbo_handle);
    glBindBuffer(GL_ARRAY_BUFFER, buf.vbo_handle);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(vertex), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), sizeof(vec3));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), 2 * sizeof(vec3));

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    return buf;
}

void vbo_free(vertexbuffer_t *buf)
{
    glDeleteBuffers(1, &buf->vbo_handle);
    glDeleteVertexArrays(1, &buf->vao_handle);
}

void vbo_draw(vertexbuffer_t *buf)
{
    glBindVertexArray(buf->vao_handle);
    glDrawArrays(buf->mode, 0, buf->vx_count);
    glBindVertexArray(0);
}
