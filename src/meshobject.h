#pragma once

#include "vertexbuffer.h"
#include "shader.h"

typedef struct meshobject_t {
    vertexbuffer_t vbo;
    shader_t shader;
} meshobject_t;

meshobject_t new_meshobject(shader_t shader, vertexbuffer_t vbo);
void free_meshobject(meshobject_t *mesh);
void draw_meshobject(meshobject_t *mesh);
