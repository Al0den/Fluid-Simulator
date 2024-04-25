#ifndef ENGINE_H
#define ENGINE_H

#pragma once

#include "includes.h"
#include "objects/particle.h"

#include <Metal/Metal.hpp>

class Engine {
public:
    void init(MTL::Device *device);

    MTL::Device *_mDevice;
    MTL::Device *device;

    MTL::ComputePipelineState *_mAddFunctionPSO;
    MTL::ComputePipelineState *_mDensityMapUpdaterPSO;
    MTL::ComputePipelineState *_mGradientCalculatorPSO;
    MTL::ComputePipelineState *_mDensityCoeffPSO;
   
 
    MTL::CommandQueue *_mCommandQueue;

    MTL::Buffer *particles;
    MTL::Buffer *density_map;
    MTL::Buffer *gradientX;
    MTL::Buffer *gradientY;
    MTL::Buffer *mouseData;
    MTL::Buffer *density_coeffs;

    void step();

    void encodeParticleUpdaterCommand(MTL::ComputeCommandEncoder *computeCommandEncoder);
    void encodeDensityUpdaterCommand(MTL::ComputeCommandEncoder *computeCommandEncoder);
    void encodeGradientCalculatorCommand(MTL::ComputeCommandEncoder *computeCommandEncoder);
    void encodeDensityCoeffCommand(MTL::ComputeCommandEncoder *computeCommandEncoder);
    
    void clear_density_map();
    void clear_gradient_buffers();

    void ApplyExternalForce();

    float minimum_density;
    float maximum_density;

    int steps;
    
private:
    void init_particles();
    void init_density_map();
    void init_gradient_buffers();
    void init_mouse_data();
    void init_density_coeffs();
};

#endif // ENGINE_H