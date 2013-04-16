#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "voxelengine.h"

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    if(voxelengine_init() != 0) {
        printf("voxelengine_init() failed\n");
    }

    return voxelengine_run();
}
