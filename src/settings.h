#pragma once

#define HEIGHT 800
#define WIDTH 800

#define MAX_PARTICLES 3000

#define DENSITY_RADIUS 100

#define GRAVITY 0

#define STIFFNESS 35
#define REST_DENSITY 0.0013
#define CLAMP_MULTIPLIER -0.1
#define FRICTION_FACTOR 0.87

#define MOUSE_RANGE 100

#define PARTICLE_EDGE 2

#define DENSITY_RESOLUTION 5

#define TPS 120
//From x and y coordinate get the position of the particle in the array
#define GET_INDEX(x, y) (WIDTH * y + x)