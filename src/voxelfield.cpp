#include "voxelfield.h"
#include "simplexnoise.h"

voxelfield vf_new(double granularity)
{
    voxelfield vf;
    vf.granularity = granularity;
    return vf;
}

double vf_value_at(voxelfield *vf, double x, double y, double z)
{
    return raw_noise_3d(x * vf->granularity, y * vf->granularity, z * vf->granularity);
}

int vf_neighbor_bits(voxelfield *vf, double x, double y, double z, double tolerance)
{
    int ret = 0, _x, _y, _z;
    int curbit = 31;

    for(_y = -1; _y <= 1; _y++) {
        for(_z = -1; _z <= 1; _z++) {
            for(_x = -1; _x <= 1; _x++) {
                if(vf_value_at(vf, x+_x, y+_y, z+_z) > tolerance) {
                    ret |= (1 << curbit);
                }
                curbit -= 1;
            }
        }
    }
    return ret;
}

