//------------------------------------------
// shader.h
//
// Fancy shader wrapper. Takes care of
// loading shader sources from the given
// paths, compiles and links shader program.
// Also defines convenience functions for
// setting uniforms.
//-------------------------------------------
#pragma once

#include <GL/gl.h>

class Shader
{
    public:
        Shader(const char *vert_file, const char *frag_file);
        ~Shader();

        void setUniform1f(char *name, float v1);
        void setUniform3f(char *name, float v1, float v2, float v3);
        void setUniform4f(char *name, float v1, float v2, float v3, float v4);

        void setUniform1i(char *name, int v1);

        void setUniformMatrix3fv(char *name, float *mat);
        void setUniformMatrix4fv(char *name, float *mat);

        GLuint handle;
        bool is_valid;
};
