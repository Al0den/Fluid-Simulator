#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION

#include "engine/engine.h"
#include "render/display.h"
#include <cstdlib>

#include <Metal/Metal.hpp>

int main() {
    srand(time(NULL));
    MTL::Device *device = MTL::CreateSystemDefaultDevice();
    Engine engine;
    Display display;
    engine.init(device);
    display.init();

    while(true) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }
        for (int i=0; i<1; i++) {
            engine.step();
        }
        display.update(engine);
        SDL_Delay(1000/TPS);
    }
}