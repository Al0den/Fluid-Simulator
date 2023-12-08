#ifndef DISPLAY_H
#define DISPLAY_H
#pragma once

#include <thread>
#include "/opt/homebrew/include/SDL2/SDL.h"
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
    SDL_Renderer* renderer;
};

#endif // DISPLAY_H