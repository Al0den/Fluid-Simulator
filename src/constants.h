#pragma once

#define MAX_PARTICLES 6000
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 500
#define DENSITY_RADIUS 100
#define VISCOSITY_RADIUS 20

#define GRAVITY 0
#define VISCOSITY 5

#define STIFFNESS 35
#define REST_DENSITY 0.0002
#define CLAMP_MULTIPLIER -1

#define PARTICLE_EDGE 4

#define TPS 60

//From x and y coordinate get the position of the particle in the array
#define GET_INDEX(x, y) (SCREEN_WIDTH * y + x)