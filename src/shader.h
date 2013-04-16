#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

typedef struct shader_t {
    GLuint handle;
    int is_valid;
} shader_t;

shader_t new_shader(char *vert_file, char *frag_file);
void free_shader(shader_t *s);

void setUniform1f(shader_t *s, char *name, float v1);
void setUniform3f(shader_t *s, char *name, float v1, float v2, float v3);
void setUniform4f(shader_t *s, char *name, float v1, float v2, float v3, float v4);

void setUniform1i(shader_t *s, char *name, int v1);

void setUniformMatrix3fv(shader_t *s, char *name, float *mat);
void setUniformMatrix4fv(shader_t *s, char *name, float *mat);
