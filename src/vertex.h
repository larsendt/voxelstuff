#pragma once

#include <GL/gl.h>

typedef struct vec3 {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} vec3;

typedef struct vec4 {
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
} vec4;

typedef struct vertex {
    vec3 pos;
    vec3 norm;
    vec4 color;
} vertex;

vertex vx_new(float x, float y, float z, float nx, float ny, float nz, float r, float g, float b, float a);

