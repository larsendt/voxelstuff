#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(GLenum mode, vertex *vertices, unsigned int count)
{
    this->mode = mode;
    this->vx_count = count;

    glGenVertexArrays(1, &vao_handle);
    glBindVertexArray(vao_handle);

    glGenBuffers(1, &vbo_handle);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_handle);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(vertex), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)sizeof(vec3));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(2 * sizeof(vec3)));

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &vbo_handle);
    glDeleteVertexArrays(1, &vao_handle);
}

void VertexBuffer::draw()
{
    glBindVertexArray(vao_handle);
    glDrawArrays(mode, 0, vx_count);
    glBindVertexArray(0);
}
