#ifndef DISPLAY_H
#define DISPLAY_H
#pragma once

#include <thread>
#include "objects/particle.h"
#include "engine/engine.h"

class Display {
public:
    void init();
    void update(Engine engine);
    
    SDL_Window* window;
    SDL_Surface* window_surface;
    

private:
    void drawParticles(Engine engine);
    void drawDensityMap(Engine engine);
    SDL_Renderer* renderer;
};

#endif // DISPLAY_H