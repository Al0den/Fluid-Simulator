#include "particle.h"
#include "includes.h"

void Particle::init(int i) {
    float rand_float = (float)rand() / RAND_MAX;
    this->x = rand() % (WIDTH) + rand_float;
    this->y = rand() % (HEIGHT) + rand_float;
    this->velocity_x = 0;
    this->velocity_y = 0;
}

void Particle::Clamp() {
    printf("Clamping particle at x: %f, y: %f\n", this->x, this->y);
    if (this->x < 0) {
        this->x = 0;
        this->velocity_x = -CLAMP_MULTIPLIER;
    }
    if (this->x > WIDTH) {
        this->x = WIDTH;
        this->velocity_x = -CLAMP_MULTIPLIER;
    }
    if (this->y < 0) {
        this->y = 0;
        this->velocity_y = -CLAMP_MULTIPLIER;
    }
    if (this->y > HEIGHT) {
        this->y = HEIGHT;
        this->velocity_y *= -CLAMP_MULTIPLIER;
    }
    printf("Particle clamped at x: %f, y: %f\n", this->x, this->y);
}