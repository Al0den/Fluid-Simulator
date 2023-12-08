#include "particle.h"
#include "../constants.h"

#include <iostream>

void Particle::init(int i) {
    float rand_float = (float)rand() / RAND_MAX;
    this->x = rand() % (SCREEN_WIDTH) + rand_float;
    this->y = rand() % (SCREEN_HEIGHT) + rand_float;
    this->velocity_x = (rand() % 2) - 1;
    this->velocity_y = (rand() % 2) - 1;
}

void Particle::Clamp() {
    if (this->x < 0) {
        this->x = 0;
        this->velocity_x = -CLAMP_MULTIPLIER;
    }
    if (this->x > SCREEN_WIDTH) {
        this->x = SCREEN_WIDTH;
        this->velocity_x = -CLAMP_MULTIPLIER;
    }
    if (this->y < 0) {
        this->y = 0;
        this->velocity_y = -CLAMP_MULTIPLIER;
    }
    if (this->y > SCREEN_HEIGHT) {
        this->y = SCREEN_HEIGHT;
        this->velocity_y *= -CLAMP_MULTIPLIER;
    }
}