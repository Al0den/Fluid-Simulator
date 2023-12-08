#pragma once

#define MAX_PARTICLES 6000
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 500
#define DENSITY_RADIUS 100
#define GRAVITY 12

#define STIFFNESS 75
#define REST_DENSITY 0.0000002
#define CLAMP_MULTIPLIER 0

#define PARTICLE_EDGE 4

#define TPS 60

//From x and y coordinate get the position of the particle in the array
#define GET_INDEX(x, y) (SCREEN_WIDTH * y + x)