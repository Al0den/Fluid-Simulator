#include "engine.h"
#include "../objects/particle.h"

#include <Metal/Metal.hpp>

void Engine::step() {
    // Create a command buffer to hold commands.
    MTL::CommandBuffer *commandBuffer = _mCommandQueue->commandBuffer();
    MTL::ComputeCommandEncoder *computeEncoder = commandBuffer->computeCommandEncoder();

    encodeParticleUpdaterCommand(computeEncoder);
    encodeDensityUpdaterCommand(computeEncoder);
    encodeGradientCalculatorCommand(computeEncoder);
    encodeViscosityCommand(computeEncoder);

    computeEncoder->endEncoding();
    commandBuffer->commit();

    commandBuffer->waitUntilCompleted();

    this->ApplyExternalForce();
}

void Engine::ApplyExternalForce() {
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    bool space_down = SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE];
    bool shift_down = SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LSHIFT];
    bool ctrl_down = SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LCTRL];
    Particle *particles = (Particle*)this->particles->contents();

    if (shift_down) {
        for (int i=0; i<MAX_PARTICLES; i++) {
            float distance = sqrt(pow(mouse_x - particles[i].x, 2) + pow(mouse_y - particles[i].y, 2));
            if (distance < 75) {
                float force = (75 - distance) / 75 * 0.3;
                particles[i].velocity_x -= (mouse_x - particles[i].x) * force;
                particles[i].velocity_y -= (mouse_y - particles[i].y) * force;
            }
        }
    }
    if (ctrl_down) {
        for (int i=0; i<MAX_PARTICLES; i++) {
            float distance = sqrt(pow(mouse_x - particles[i].x, 2) + pow(mouse_y - particles[i].y, 2));
            if (distance < 75) {
                float force = (75 - distance) / 75 * 0.2;
                particles[i].velocity_x += (mouse_x - particles[i].x) * force;
                particles[i].velocity_y += (mouse_y - particles[i].y) * force;
            }
        }
    }
    if(space_down) {
        for (int i=0; i<MAX_PARTICLES; i++) {
            float distance = sqrt(pow(mouse_x - particles[i].x, 2) + pow(mouse_y - particles[i].y, 2));
            float rand_float = (float)rand() / RAND_MAX;
            if(distance < 75) {
                particles[i].x = 100 + rand() % 50 + rand_float;
                particles[i].y = 100 + rand() % 50 + rand_float;
            }
        }
    }
}
