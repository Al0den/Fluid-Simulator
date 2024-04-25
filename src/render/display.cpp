#include "includes.h"
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

    this->window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
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
    
    float max_speed = 0;
    float min_speed = 13
    ;
    for(int i=0; i<MAX_PARTICLES; i++) {
        float speed = sqrt(particles[i].velocity_x * particles[i].velocity_x + particles[i].velocity_y * particles[i].velocity_y);
        if (speed > max_speed) {
            max_speed = speed;
        }
        if (speed < min_speed) {
            min_speed = speed;
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        drawFilledCircle(renderer, (int)particles[i].x, (int)particles[i].y, 1);
    }
}

void Display::drawDensityMap(Engine engine) {
    float* density_map = (float*)engine.density_map->contents();
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    // Create a buffer to hold the pixel data
    Uint32* pixels = new Uint32[WIDTH * HEIGHT];

    float min_density = engine.minimum_density;
    float max_density = engine.maximum_density;

    // For every pixel, calculate the color based on the density value
    for (int y = 0; y < HEIGHT; y += DENSITY_RESOLUTION) {
        for (int x = 0; x < WIDTH; x += DENSITY_RESOLUTION) {
            int i = y * WIDTH + x;

            float normalizedDensity = (density_map[i] - min_density) / (max_density - min_density);
            normalizedDensity = std::clamp(normalizedDensity, 0.0f, 1.0f); // Clamp the value between 0 and 1

            // Calculate HSL values for interpolation
            float h, s, l;
            h = 240.0f - normalizedDensity * 240.0f; // Range from 240 (blue) to 0 (red)
            s = 1.0f;
            l = 0.5f;

            // Convert HSL to RGB color
            SDL_Color densityColor = HSLToRGB(h, s, l);

            // Set the pixel color in the buffer for the 3x3 rectangle
            for (int dy = 0; dy < DENSITY_RESOLUTION; dy++) {
                for (int dx = 0; dx < DENSITY_RESOLUTION; dx++) {
                    if (y + dy < HEIGHT && x + dx < WIDTH) {
                        int j = (y + dy) * WIDTH + (x + dx);
                        pixels[j] = (densityColor.r << 16) | (densityColor.g << 8) | densityColor.b;
                    }
                }
            }
        }
    }

    // Update the texture with the pixel data
    SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(Uint32));

    // Draw the texture
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Clean up
    SDL_DestroyTexture(texture);
    delete[] pixels;
}


void Display::update(Engine engine) {
    
    float* density_map = (float*)engine.density_map->contents();
    for (int i = 0; i < HEIGHT * WIDTH; i++) {
        if (density_map[i] < engine.minimum_density) {
            engine.minimum_density = density_map[i];
        }
        if (density_map[i] > engine.maximum_density) {
            engine.maximum_density = density_map[i];
        }
    }
    
    this->drawDensityMap(engine);

    this->drawParticles(engine);

    SDL_RenderPresent(this->renderer);
}