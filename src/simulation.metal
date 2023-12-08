#include "constants.h"
#include "objects/particle.h"
#include <metal_stdlib>

using namespace metal;

float CalculatePressureForce(float density);
float Smoothing(float radius, float dist);
void ClampParticle(Particle p);

kernel void ParticleStep(device Particle* particles [[buffer(0)]], device const float* gradientX [[buffer(1)]], device const float* gradientY [[buffer(2)]], device const float* density_map [[buffer(3)]], uint id [[thread_position_in_grid]]) {
    Particle p = particles[id];
    float x = p.x;
    float y = p.y;

    int grad_id = int(x) + int(y) * SCREEN_WIDTH;
    p.velocity_x += gradientX[grad_id] * 12000.0 * 8000 / MAX_PARTICLES * CalculatePressureForce(density_map[grad_id]);
    p.velocity_y += gradientY[grad_id] * 12000.0 * 8000 / MAX_PARTICLES * CalculatePressureForce(density_map[grad_id]);

    p.x += p.velocity_x;
    p.y += p.velocity_y;
    p.velocity_x *= 0.83;
    p.velocity_y *= 0.83;
    p.y += GRAVITY;

    ClampParticle(p);
    
    particles[id] = p;
}

kernel void DensityMapUpdate(device const Particle* particles [[buffer(0)]], device float* density_map [[buffer(1)]], device const float* density_coeffs [[buffer(2)]], uint id [[thread_position_in_grid]]) {
    int block_x = (id) % SCREEN_WIDTH;
    int block_y = (id) / SCREEN_WIDTH;

    float density = 0.0;
    for (int i = 0; i < MAX_PARTICLES; i++) {
        Particle p = particles[i];
        float distance = sqrt(pow(float(block_x) - p.x, 2.0) + pow(float(block_y) - p.y, 2.0));
        if (distance < DENSITY_RADIUS) {
            density += Smoothing(DENSITY_RADIUS, distance);
        }
    }
    density_map[id] = density * density_coeffs[id];
}

kernel void GradientMapUpdate(device const float* density_map[[buffer(0)]], device float* gradientX[[buffer(1)]], device float* gradientY[[buffer(2)]], uint id [[thread_position_in_grid]]) {
    gradientY[id] = -density_map[id + SCREEN_WIDTH] + density_map[id - SCREEN_WIDTH];
    gradientX[id] = -density_map[id + 1] + density_map[id - 1];
}

kernel void DensityCoeffInit(device float* density_coeffs [[buffer(0)]], uint id [[thread_position_in_grid]]) {
    float in_range = 0.0;
    float out_range = 0.0;

    int x = (id) % SCREEN_WIDTH;
    int y = (id) / SCREEN_WIDTH;

    for (int i=-DENSITY_RADIUS + 1; i<=DENSITY_RADIUS; i++) {
        for (int j=-DENSITY_RADIUS + 1; j<=DENSITY_RADIUS; j++) {
            float distance = sqrt(pow(float(i), 2.0) + pow(float(j), 2.0));
            if (distance < DENSITY_RADIUS) {
                if(x + i >= 0 && x + i < SCREEN_WIDTH && y + j >= 0 && y + j < SCREEN_HEIGHT) {
                    in_range += Smoothing(DENSITY_RADIUS, distance);
                } else {
                    out_range += Smoothing(DENSITY_RADIUS, distance);
                }
            }
        }
    }

    density_coeffs[id] = float(in_range + out_range) / float(in_range);
}

void ClampParticle(Particle p) {
    if (p.x <= PARTICLE_EDGE) {
        p.x = PARTICLE_EDGE + 2;
        p.velocity_x *= 0;
    }
    if (p.x >= SCREEN_WIDTH - PARTICLE_EDGE) {
        p.x = SCREEN_WIDTH - PARTICLE_EDGE - 2;
        p.velocity_x *= 0;
    }
    if (p.y < PARTICLE_EDGE) {
        p.y = PARTICLE_EDGE + 2;
        p.velocity_y *= -0;
    }
    if (p.y >= SCREEN_HEIGHT - PARTICLE_EDGE) {
        p.y = SCREEN_HEIGHT - PARTICLE_EDGE - 2;
        p.velocity_y *= -0;
    }
}

float CalculatePressureForce(float density) {
    float densityError = density - REST_DENSITY;
    return densityError * STIFFNESS;
}


float Smoothing(float radius, float dist) {
    if (dist > radius) return 0;
    float volume = (3.14 * pow(radius, 4.0)) / 6.0;
    return (radius - dist) * (radius - dist) / volume;
}