
#pragma once

class Particle {
public:
    float x, y;
    float velocity_x, velocity_y;

    void init(int i);
    void Clamp();
};