#ifndef BODY_H
#define BODY_H

#include "Vec3.h"

// Represents a single N-body particle for Verlet integration
struct Body {
    Vec3 pos;   // current position
    Vec3 vel;   // current velocity
    Vec3 acc;   // current acceleration (needed by Verlet)
    double mass; // particle mass

    // Default constructor: zero vectors and unit mass
    HD Body() : pos(), vel(), acc(), mass(1.0) {}
};

#endif // BODY_H
