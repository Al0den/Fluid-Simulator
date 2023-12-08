#include <stdio.h>
#include <iostream>
#include <thread>
#include <functional>
#include <cmath>
#include <algorithm>

#include "/opt/homebrew/include/SDL2/SDL.h"
#include "constants.h"
#include "display.h"
#include "objects/particle.h"

// Define colors
const SDL_Color blueColor = {0, 0, 255, 255};
const SDL_Color yellowColor = {255, 255, 0, 255};
const SDL_Color orangeColor = {255, 165, 0, 255};
const SDL_Color redColor = {255, 0, 0, 255};

void Display::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize the SDL2 library\n");
        return;
    }

    this->window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!this->window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        // Handle error
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!this->renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        // Handle error
    }
    SDL_UpdateWindowSurface(this->window);
}

SDL_Color HSLToRGB(float h, float s, float l) {
    float c = (1 - std::abs(2 * l - 1)) * s;
    float x = c * (1 - std::abs(fmod(h / 60.0, 2) - 1));
    float m = l - c / 2;

    float r, g, b;
    if (h >= 0 && h < 60) {
        r = c;
        g = x;
        b = 0;
    } else if (h >= 60 && h < 120) {
        r = x;
        g = c;
        b = 0;
    } else if (h >= 120 && h < 180) {
        r = 0;
        g = c;
        b = x;
    } else if (h >= 180 && h < 240) {
        r = 0;
        g = x;
        b = c;
    } else if (h >= 240 && h < 300) {
        r = x;
        g = 0;
        b = c;
    } else {
        r = c;
        g = 0;
        b = x;
    }

    SDL_Color rgbColor;
    rgbColor.r = static_cast<Uint8>((r + m) * 255);
    rgbColor.g = static_cast<Uint8>((g + m) * 255);
    rgbColor.b = static_cast<Uint8>((b + m) * 255);
    rgbColor.a = 255;

    return rgbColor;
}

void drawFilledCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; ++w) {
        for (int h = 0; h < radius * 2; ++h) {
            int dx = radius - w; // Horizontal offset
            int dy = radius - h; // Vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void Display::drawParticles(Engine engine) {
    Particle* particles = (Particle*)engine.particles->contents();
    float* density_map = (float*)engine.density_map->contents();
    float* gradientX = (float*)engine.gradientX->contents();
    float* gradientY = (float*)engine.gradientY->contents();
    float* density_coeffs = (float*)engine.density_coeffs->contents();

    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255); // Set color to white (you can change this)
    SDL_RenderClear(this->renderer);
    //Draw full screen black
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = SCREEN_WIDTH;
    rect.h = SCREEN_HEIGHT;
    SDL_RenderFillRect(this->renderer, &rect);
    float max_speed = 8;
    float min_speed = 15;
  
    for (int i = 0; i < MAX_PARTICLES; ++i) {
        // Calculate speed and normalize it between 0 and 1
        float speed = sqrt(particles[i].velocity_x * particles[i].velocity_x + particles[i].velocity_y * particles[i].velocity_y);
        float normalizedSpeed = (speed - min_speed) / (max_speed - min_speed);
        normalizedSpeed = std::clamp(normalizedSpeed, 0.0f, 1.0f); // Clamp the value between 0 and 1

        // Calculate HSL values for interpolation
        float h, s, l;
        if (normalizedSpeed <= 0.5) {
            // Blue to Yellow
            h = 240.0f - normalizedSpeed * 240.0f; // Range from 240 (blue) to 60 (yellow)
            s = 1.0f;
            l = 0.5f;
        } else {
            // Yellow to Red
            h = 60.0f + (normalizedSpeed - 0.5f) * 300.0f; // Range from 60 (yellow) to 0 (red)
            s = 1.0f;
            l = 0.5f;
        }

        // Adjust maximum speed color to deep red
        if (normalizedSpeed >= 1.0f) {
            h = 0.0f; // Red hue
            s = 1.0f;
            l = 0.5f;
        }

        // Convert HSL to RGB color
        SDL_Color particleColor = HSLToRGB(h, s, l);
        SDL_SetRenderDrawColor(renderer, particleColor.r, particleColor.g, particleColor.b, particleColor.a);
        drawFilledCircle(renderer, (int)particles[i].x, (int)particles[i].y, 1);
    }
    SDL_RenderPresent(renderer);
}

void Display::update(Engine engine) {
    this->drawParticles(engine);
}