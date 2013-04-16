#include "voxelengine.h"
#include "voxelfield.h"
#include "utils.h"
#include "meshobject.h"

#include <GL/glfw.h>
#include <cstdio>
#include <cstdlib>

typedef struct engine_state {
    MeshObject *mesh;
    Shader *shader;
    VertexBuffer *vbo;
} engine_state;

engine_state engine_init();
void engine_draw(engine_state *state);
void resize(int x, int y);

int voxelengine_init()
{
    if(!glfwInit())
        return -1;

    return 0;
}

int voxelengine_run()
{
    if(!glfwOpenWindow(800, 600, 8, 8, 8, 0, 24, 0, GLFW_WINDOW))
        return -1;

    glfwSetWindowSizeCallback(&resize);
    engine_state state = engine_init();

    while(glfwGetWindowParam(GLFW_OPENED)) {
        engine_draw(&state);
        glfwSwapBuffers();
        check_gl_error(__FILE__, __LINE__);
    }

    delete state.mesh;
    delete state.shader;
    delete state.vbo;
    return 0;
}

engine_state engine_init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    int sz = 1;
    vertex vertices[6];
    vertices[0] = vx_new(-sz, -sz, 0, 0, 0, 1, 1, 1, 1, 1);
    vertices[1] = vx_new( sz, -sz, 0, 0, 0, 1, 1, 1, 1, 1);
    vertices[2] = vx_new(-sz,  sz, 0, 0, 0, 1, 1, 1, 1, 1);
    vertices[3] = vx_new(-sz,  sz, 0, 0, 0, 1, 1, 1, 1, 1);
    vertices[4] = vx_new( sz, -sz, 0, 0, 0, 1, 1, 1, 1, 1);
    vertices[5] = vx_new( sz,  sz, 0, 0, 0, 1, 1, 1, 1, 1);

    engine_state state;
    state.vbo = new VertexBuffer(GL_TRIANGLES, vertices, 6);
    state.shader = new Shader("../shaders/plain.vert", "../shaders/plain.frag");

    if(!state.shader->is_valid) {
        fprintf(stderr, "Failed to load shader\n");
        exit(1);
    }

    state.mesh = new MeshObject(state.shader, state.vbo);
    return state;
}

void engine_draw(engine_state *state)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    state->mesh->draw();
    /*glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
    glEnd();*/
}

void resize(int x, int y)
{
    float aspect = (float)x/y;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45.0, aspect, 1, 500);
    glOrtho(-aspect, aspect, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
