#pragma once

typedef struct voxelfield {
    double granularity;
} voxelfield;

// granularity scales coordinates:
//     e.g. with a granularity of 0.1 (3, 0, 1) -> (0.3, 0, 0.1)
voxelfield vf_new(double granularity);

// returns the value at the requested coordinates, scaled
// by the granularity of the vf
double vf_value_at(voxelfield *vf, double x, double y, double z);

// returns an int with bits set according to which neighbors are
// above the specified tolerance
// only 27 high-bits are used
// bit format example: +-0 means neighbor in the +x, -y and same z coords
// [---, 0--, +--, --0, 0-0, +-0, --+, 0-+, +-+, -0-, 00-, +0-,
//  -00, 000, +00, -0+, 00+, +0+, -+-, 0+-, ++-, -+0, 0+0, ++0,
//  -++, 0++, +++,]
// testing example: to test ---: nbits & (1 << 31)
//                  to test +00: nbits & (1 << 17)
int vf_neighbor_bits(voxelfield *vf, double x, double y, double z, double tolerance);

