#include "shader.h"
#include <stdio.h>
#include <stdlib.h>

char *get_file_src(char *filename);
GLuint compile_shader(GLenum type, char *filename, int *status);
GLuint compile_program(GLuint vertex_shader, GLuint fragment_shader, int *status);

shader_t new_shader(char *vert_file, char *frag_file)
{
    shader_t s;
    int status;
    GLuint vhandle = compile_shader(GL_VERTEX_SHADER, vert_file, &status);

    if(!status) {
        s.is_valid = 0;
        return s;
    }

    GLuint fhandle = compile_shader(GL_FRAGMENT_SHADER, frag_file, &status);

    if(!status) {
        s.is_valid = 0;
        return s;
    }

    s.handle = compile_program(vhandle, fhandle, &status);

    if(!status) {
        s.is_valid = 0;
        return s;
    }

    s.is_valid = 1;
    return s;
}

void free_shader(shader_t *s)
{
    glDeleteProgram(s->handle);
}

char *get_file_src(char *filename)
{
    char *file_src;
    FILE *f = fopen(filename, "r");

    if(!f) {
        fprintf(stderr, "Unable to load file: '%s'\n", filename);
        return NULL;
    }

    int sz;

    fseek(f, 0, SEEK_END);
    sz = ftell(f);
    fseek(f, 0, SEEK_SET);

    file_src = malloc(sz * sizeof(*file_src));
    fread(file_src, sizeof(*file_src), sz, f);
    return file_src;
}

GLuint compile_shader(GLenum type, char *filename, int *status)
{
    GLint shader_status;
    GLint info_log_size;
    char *info_log;

    char *src = get_file_src(filename);

    if(!src)
        return 0;

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, (GLint*)NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_status);
    if(shader_status == GL_TRUE) {
        printf("Compiled %s\n", filename);
        *status = 1;
    }
    else {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_size);
        info_log = malloc(info_log_size);
        glGetShaderInfoLog(shader, info_log_size, &info_log_size, info_log);
        fprintf(stderr, "Error compiling %s:\n%s\n", filename, info_log);
        free(info_log);
        glDeleteShader(shader);
        shader = 0;
        *status = 0;
    }

    free(src);
    return shader;
}

GLuint compile_program(GLuint vertex_shader, GLuint fragment_shader, int *status)
{
    GLint program_status;
    GLint info_log_size;
    char *info_log;

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &program_status);
    if(program_status == GL_TRUE) {
        *status = 1;
    }
    else {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_size);
        info_log = malloc(info_log_size);
        glGetProgramInfoLog(program, info_log_size, &info_log_size, info_log);
        fprintf(stderr, "Error linking program:\n%s\n", info_log);
        free(info_log);
        glDeleteProgram(program);
        *status = 0;
    }

    return program;
}

void setUniform1f(shader_t *s, char *name, float v1)
{
    GLuint loc = glGetUniformLocation(s->handle, name);
    glUniform1f(loc, v1);
}


void setUniform3f(shader_t *s, char *name, float v1, float v2, float v3)
{
    GLuint loc = glGetUniformLocation(s->handle, name);
    glUniform3f(loc, v1, v2, v3);
}

void setUniform4f(shader_t *s, char *name, float v1, float v2, float v3, float v4)
{
    GLuint loc = glGetUniformLocation(s->handle, name);
    glUniform4f(loc, v1, v2, v3, v4);
}

void setUniform1i(shader_t *s, char *name, int v1)
{
    GLuint loc = glGetUniformLocation(s->handle, name);
    glUniform1i(loc, v1);
}

void setUniformMatrix3fv(shader_t *s, char *name, float *mat)
{
    GLuint loc = glGetUniformLocation(s->handle, name);
    glUniformMatrix3fv(loc, 1, 0, mat);
}

void setUniformMatrix4fv(shader_t *s, char *name, float *mat)
{
    GLuint loc = glGetUniformLocation(s->handle, name);
    glUniformMatrix4fv(loc, 1, 0, mat);
}
