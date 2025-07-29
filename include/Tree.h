#ifndef TREE_H
#define TREE_H

#include "Vec3.h"
#include <cstdint>

// Sentinel value for no child index
static constexpr int32_t NO_CHILD = -1;

// Node structure for Barnes-Hut octree
// If bodyIndex >= 0, treat this node as a leaf; otherwise recurse on children.
struct Node {
    Vec3 center;            // center of this octant
    double halfWidth;       // half the edge length of the cube
    Vec3 COM;               // aggregated center-of-mass of bodies in this cell
    double totalMass;       // sum of masses in this cell
    int32_t children[8];    // indices of up to 8 subnodes, or NO_CHILD
    int32_t bodyIndex;      // index of the single body if leaf, else NO_CHILD

    // Default constructor: initialize bounds and indices
    HD Node()
        : center(), halfWidth(0.0), COM(), totalMass(0.0), bodyIndex(NO_CHILD) {
        for (int i = 0; i < 8; ++i) children[i] = NO_CHILD;
    }
};

#endif // TREE_H
