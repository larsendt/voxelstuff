#include "utils.h"

#include <GL/gl.h>
#include <stdio.h>

void check_gl_error(const char *file, int line)
{
    GLenum err = glGetError();
    if(err != GL_NO_ERROR) {
        switch(err) {
            case GL_INVALID_OPERATION:
                fprintf(stderr, "%s:%d: GL_INVALID_OPERATION (%d)\n", file, line, err);
                break;
            case GL_INVALID_VALUE:
                fprintf(stderr, "%s:%d: GL_INVALID_VALUE (%d)\n", file, line, err);
                break;
            case GL_INVALID_ENUM:
                fprintf(stderr, "%s:%d: GL_INVALID_ENUM (%d)\n", file, line, err);
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                fprintf(stderr, "%s:%d: GL_INVALID_FRAMEBUFFER_OPERATION (%d)\n", file, line, err);
                break;
            case GL_OUT_OF_MEMORY:
                fprintf(stderr, "%s:%d: GL_OUT_OF_MEMORY (%d)\n", file, line, err);
                break;
            case GL_STACK_UNDERFLOW:
                fprintf(stderr, "%s:%d: GL_STACK_UNDERFLOW (%d)\n", file, line, err);
                break;
            case GL_STACK_OVERFLOW:
                fprintf(stderr, "%s:%d: GL_STACK_OVERFLOW (%d)\n", file, line, err);
                break;
            default:
                fprintf(stderr, "%s:%d: Unknown OpenGL Error (%d)\n", file, line, err);
        }
    }
}
