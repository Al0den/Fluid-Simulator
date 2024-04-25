#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION

#include "includes.h"
#include "engine/engine.h"
#include "render/display.h"

#include <cstdlib>
#include <chrono>

#include <Metal/Metal.hpp>

int main() {
    srand(time(NULL));
    MTL::Device *device = MTL::CreateSystemDefaultDevice();
    Engine engine;
    Display display;
    engine.init(device);
    display.init();

    float time_step = 0;
    float time_display = 0;

    while(true) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }

        auto start_engine = std::chrono::high_resolution_clock::now();
        engine.step();
        auto end_engine = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff_engine = end_engine - start_engine;
        time_step += diff_engine.count();

        auto start_display = std::chrono::high_resolution_clock::now();
        display.update(engine);
        auto end_display = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff_display = end_display - start_display;
        time_display += diff_display.count();

        printf("Step percentage: %f0, Display percentage: %f, Step Number: %d\n", time_step/(time_step + time_display) * 100, time_display/(time_step + time_display) * 100, engine.steps);
        
    }
}