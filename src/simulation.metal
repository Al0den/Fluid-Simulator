

#include "objects/particle.h"
#include "settings.h"
#include <metal_stdlib>

using namespace metal;

float CalculatePressureForce(float density);
float Smoothing(float radius, float dist);
float ViscositySmoothing(float radius, float dist);

kernel void ParticleStep(device Particle* particles [[buffer(0)]], device const float* gradientX [[buffer(1)]], device const float* gradientY [[buffer(2)]], device const float* density_map [[buffer(3)]], uint id [[thread_position_in_grid]]) {
    Particle p = particles[id];
    float x = p.x;
    float y = p.y;

    int grad_id = int(x) + int(y) * WIDTH;
    
    p.velocity_x += gradientX[grad_id] * 12000.0 * 8000 / MAX_PARTICLES * CalculatePressureForce(density_map[grad_id]);
    p.velocity_y += gradientY[grad_id] * 12000.0 * 8000 / MAX_PARTICLES * CalculatePressureForce(density_map[grad_id]);
    p.velocity_x *= FRICTION_FACTOR;
    p.velocity_y *= FRICTION_FACTOR;

    p.x += p.velocity_x;
    p.y += p.velocity_y;
    p.y += GRAVITY;
    if (p.x <= PARTICLE_EDGE) {
        p.x = PARTICLE_EDGE;
        p.velocity_x *= CLAMP_MULTIPLIER;
    }
    else if (p.x >= WIDTH - PARTICLE_EDGE) {
        p.x = WIDTH - PARTICLE_EDGE;
        p.velocity_x *= CLAMP_MULTIPLIER;
    }
    if (p.y < PARTICLE_EDGE) {
        p.y = PARTICLE_EDGE;
        p.velocity_y *= CLAMP_MULTIPLIER;
    }
    else if (p.y >= HEIGHT - PARTICLE_EDGE) {
        p.y = HEIGHT - PARTICLE_EDGE;
        p.velocity_y *= CLAMP_MULTIPLIER;
    }
    particles[id] = p;
}

kernel void DensityMapUpdate(device Particle* particles [[buffer(0)]], device float* density_map [[buffer(1)]], device const float* density_coeffs [[buffer(2)]], uint id [[thread_position_in_grid]]) {
    int block_x = (id) % WIDTH;
    int block_y = (id) / WIDTH;

    float density = 0.0;
    for (int i = 0; i < MAX_PARTICLES; i++) {
        Particle p = particles[i];
        float dx = float(block_x) - p.x;
        float dy = float(block_y) - p.y;
        float distance = sqrt(dx * dx + dy * dy);
        if (distance < DENSITY_RADIUS) {
            density += Smoothing(DENSITY_RADIUS, distance);
        }
    }
    density_map[id] = density * density_coeffs[id];
}

kernel void GradientMapUpdate(device const float* density_map[[buffer(0)]], device float* gradientX[[buffer(1)]], device float* gradientY[[buffer(2)]], uint id [[thread_position_in_grid]]) {
    gradientY[id] = -density_map[id + WIDTH] + density_map[id - WIDTH];
    gradientX[id] = -density_map[id + 1] + density_map[id - 1];
}

kernel void DensityCoeffInit(device float* density_coeffs [[buffer(0)]], uint id [[thread_position_in_grid]]) {
    float in_range = 0.0;
    float out_range = 0.0;

    int x = (id) % WIDTH;
    int y = (id) / WIDTH;

    for (int i=-DENSITY_RADIUS + 1; i<=DENSITY_RADIUS; i++) {
        for (int j=-DENSITY_RADIUS + 1; j<=DENSITY_RADIUS; j++) {
            float distance = sqrt(pow(float(i), 2.0) + pow(float(j), 2.0));
            if (distance < DENSITY_RADIUS) {
                if(x + i >= 0 && x + i < WIDTH && y + j >= 0 && y + j < HEIGHT) {
                    in_range += Smoothing(DENSITY_RADIUS, distance);
                } else {
                    out_range += Smoothing(DENSITY_RADIUS, distance);
                }
            }
        }
    }

    density_coeffs[id] = float(in_range + out_range) / float(in_range);
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

float ViscositySmoothing(float radius, float dist) {
    if (dist > radius) return 0;
    float volume = (3.14 * pow(radius, 8.0)) / 4;
    float value = max(0.0, radius * radius - dist * dist);
    return value * value * value / volume;
}