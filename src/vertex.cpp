#include "vertex.h"

// make a new vertex...
vertex vx_new(float x, float y, float z, float nx, float ny, float nz, float r, float g, float b, float a)
{
    vertex vx;
    vx.pos.x = x;
    vx.pos.y = y;
    vx.pos.z = z;
    vx.norm.x = nx;
    vx.norm.y = ny;
    vx.norm.z = nz;
    vx.color.x = r;
    vx.color.y = g;
    vx.color.z = b;
    vx.color.w = a;
    return vx;
}
