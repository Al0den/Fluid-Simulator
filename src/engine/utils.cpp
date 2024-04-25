#include "engine.h"

void Engine::clear_gradient_buffers() {
    float *gradientX = (float*)this->gradientX->contents();
    float *gradientY = (float*)this->gradientY->contents();
    for (int i = 0; i < HEIGHT * WIDTH; i++) {
        gradientX[i] = 0.0;
        gradientY[i] = 0.0;
    }
}

void Engine::clear_density_map() {
    float *density_map = (float*)this->density_map->contents();
    for (int i = 0; i < HEIGHT * WIDTH; i++) {
        density_map[i] = 0.0;
    }
}