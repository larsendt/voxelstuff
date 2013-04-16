#include "shader.h"
#include <stdio.h>
#include <stdlib.h>

char *get_file_src(const char *filename);
GLuint compile_shader(GLenum type, const char *filename, int *status);
GLuint compile_program(GLuint vertex_shader, GLuint fragment_shader, int *status);

Shader::Shader(const char *vert_file, const char *frag_file)
{
    int status;
    GLuint vhandle = compile_shader(GL_VERTEX_SHADER, vert_file, &status);

    if(!status) {
        is_valid = 0;
        return;
    }

    GLuint fhandle = compile_shader(GL_FRAGMENT_SHADER, frag_file, &status);

    if(!status) {
        is_valid = 0;
        return;
    }

    handle = compile_program(vhandle, fhandle, &status);

    if(!status) {
        is_valid = 0;
        return;
    }

    is_valid = 1;
}

Shader::~Shader()
{
    glDeleteProgram(handle);
}

void Shader::setUniform1f(char *name, float v1)
{
    GLuint loc = glGetUniformLocation(handle, name);
    glUniform1f(loc, v1);
}


void Shader::setUniform3f(char *name, float v1, float v2, float v3)
{
    GLuint loc = glGetUniformLocation(handle, name);
    glUniform3f(loc, v1, v2, v3);
}

void Shader::setUniform4f(char *name, float v1, float v2, float v3, float v4)
{
    GLuint loc = glGetUniformLocation(handle, name);
    glUniform4f(loc, v1, v2, v3, v4);
}

void Shader::setUniform1i(char *name, int v1)
{
    GLuint loc = glGetUniformLocation(handle, name);
    glUniform1i(loc, v1);
}

void Shader::setUniformMatrix3fv(char *name, float *mat)
{
    GLuint loc = glGetUniformLocation(handle, name);
    glUniformMatrix3fv(loc, 1, 0, mat);
}

void Shader::setUniformMatrix4fv(char *name, float *mat)
{
    GLuint loc = glGetUniformLocation(handle, name);
    glUniformMatrix4fv(loc, 1, 0, mat);
}

char *get_file_src(const char *filename)
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

    file_src = new char[sz];
    fread(file_src, sizeof(*file_src), sz, f);
    file_src[sz-1] = '\0';
    return file_src;
}

GLuint compile_shader(GLenum type, const char *filename, int *status)
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
        info_log = new char[info_log_size];
        glGetShaderInfoLog(shader, info_log_size, &info_log_size, info_log);
        fprintf(stderr, "Error compiling %s:\n%s\n", filename, info_log);
        delete[] info_log;
        glDeleteShader(shader);
        shader = 0;
        *status = 0;
    }

    delete[] src;
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
        info_log = new char[info_log_size];
        glGetProgramInfoLog(program, info_log_size, &info_log_size, info_log);
        fprintf(stderr, "Error linking program:\n%s\n", info_log);
        delete[] info_log;
        glDeleteProgram(program);
        *status = 0;
    }

    return program;
}

