#include "engine.h"
#include "settings.h"

void Engine::step() {
    // Create a command buffer to hold commands.
    MTL::CommandBuffer *commandBuffer = _mCommandQueue->commandBuffer();
    MTL::ComputeCommandEncoder *computeEncoder = commandBuffer->computeCommandEncoder();

    encodeParticleUpdaterCommand(computeEncoder);
    encodeDensityUpdaterCommand(computeEncoder);
    encodeGradientCalculatorCommand(computeEncoder);

    computeEncoder->endEncoding();
    commandBuffer->commit();

    commandBuffer->waitUntilCompleted();

    this->ApplyExternalForce();
    this->steps++;
}


void Engine::ApplyExternalForce() {
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    bool space_down = SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE];
    bool shift_down = SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LSHIFT];
    bool ctrl_down = SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LCTRL];
    bool right_shift_down = SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RSHIFT];
    Particle *particles = (Particle*)this->particles->contents();

    if (shift_down) {
        for (int i=0; i<MAX_PARTICLES; i++) {
            float distance = sqrt(pow(mouse_x - particles[i].x, 2) + pow(mouse_y - particles[i].y, 2));
            if (distance < MOUSE_RANGE) {
                float force = pow((MOUSE_RANGE - distance) / MOUSE_RANGE, 2);
                particles[i].velocity_x -= (mouse_x - particles[i].x) * force;
                particles[i].velocity_y -= (mouse_y - particles[i].y) * force;
            }
        }
    }
    if (ctrl_down) {
        for (int i=0; i<MAX_PARTICLES; i++) {
            float distance = sqrt(pow(mouse_x - particles[i].x, 2) + pow(mouse_y - particles[i].y, 2));
            if (distance < MOUSE_RANGE) {
                float force = pow((MOUSE_RANGE - distance) / MOUSE_RANGE, 2);
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

    if(right_shift_down) {
        for (int i=0; i<MAX_PARTICLES; i++) {
            // Get distance from center of screen
            float distance = sqrt(pow(float(WIDTH) / 2 - particles[i].x, 2) + pow(float(HEIGHT) / 2 - particles[i].y, 2));
                // Apply coming from center, of strength cos(this->steps * 0.1), stronger if closer to center
            float force = cos(this->steps * 0.1) * pow((float(WIDTH)/2 - distance) / WIDTH, 2) * 5;
            float angle = atan2(particles[i].y - float(HEIGHT) / 2, particles[i].x - float(WIDTH) / 2);
            particles[i].velocity_x += cos(angle) * force;
            particles[i].velocity_y += sin(angle) * force;
            
        }
    }

}