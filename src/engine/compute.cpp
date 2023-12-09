#include "engine.h"
#include <Metal/Metal.hpp>

#include <cstdlib>
#include <iostream>


void Engine::encodeParticleUpdaterCommand(MTL::ComputeCommandEncoder *computeEncoder) {
    computeEncoder->setComputePipelineState(_mAddFunctionPSO);
    computeEncoder->setBuffer(particles, 0, 0);
    computeEncoder->setBuffer(gradientX, 0, 1);
    computeEncoder->setBuffer(gradientY, 0, 2);
    computeEncoder->setBuffer(density_map, 0, 3);

    MTL::Size gridSize = MTL::Size::Make(MAX_PARTICLES, 1, 1);

    NS::UInteger threadGroupSize =
        _mAddFunctionPSO->maxTotalThreadsPerThreadgroup();
    if (threadGroupSize > MAX_PARTICLES) {
        threadGroupSize = MAX_PARTICLES;
    }
    MTL::Size threadgroupSize = MTL::Size::Make(threadGroupSize, 1, 1);

    computeEncoder->dispatchThreads(gridSize, threadgroupSize);
}

void Engine::encodeDensityUpdaterCommand(MTL::ComputeCommandEncoder *computeEncoder) {
    computeEncoder->setComputePipelineState(_mDensityMapUpdaterPSO);
    computeEncoder->setBuffer(particles, 0, 0);
    computeEncoder->setBuffer(density_map, 0, 1);
    computeEncoder->setBuffer(density_coeffs, 0, 2);

    MTL::Size gridSize = MTL::Size::Make(SCREEN_WIDTH * SCREEN_HEIGHT, 1, 1);

    NS::UInteger threadGroupSize =
        _mDensityMapUpdaterPSO->maxTotalThreadsPerThreadgroup();
    if (threadGroupSize > SCREEN_WIDTH * SCREEN_HEIGHT) {
        threadGroupSize = SCREEN_WIDTH * SCREEN_HEIGHT;
    }
    MTL::Size threadgroupSize = MTL::Size::Make(threadGroupSize, 1, 1);

    computeEncoder->dispatchThreads(gridSize, threadgroupSize);
}

void Engine::encodeGradientCalculatorCommand(MTL::ComputeCommandEncoder *computeEncoder) {
    computeEncoder->setComputePipelineState(_mGradientCalculatorPSO);
    computeEncoder->setBuffer(density_map, 0, 0);
    computeEncoder->setBuffer(gradientX, 0, 1);
    computeEncoder->setBuffer(gradientY, 0, 2);

    MTL::Size gridSize = MTL::Size::Make(SCREEN_WIDTH * SCREEN_HEIGHT, 1, 1);

    NS::UInteger threadGroupSize =
        _mGradientCalculatorPSO->maxTotalThreadsPerThreadgroup();
    if (threadGroupSize > SCREEN_WIDTH * SCREEN_HEIGHT) {
        threadGroupSize = SCREEN_WIDTH * SCREEN_HEIGHT;
    }
    MTL::Size threadgroupSize = MTL::Size::Make(threadGroupSize, 1, 1);

    computeEncoder->dispatchThreads(gridSize, threadgroupSize);
}

void Engine::encodeDensityCoeffCommand(MTL::ComputeCommandEncoder *computeEncoder) {
    computeEncoder->setComputePipelineState(_mDensityCoeffPSO);
    computeEncoder->setBuffer(density_coeffs, 0, 0);

    MTL::Size gridSize = MTL::Size::Make(SCREEN_WIDTH * SCREEN_HEIGHT, 1, 1);

    NS::UInteger threadGroupSize =
        _mDensityCoeffPSO->maxTotalThreadsPerThreadgroup();
    if (threadGroupSize > SCREEN_WIDTH * SCREEN_HEIGHT) {
        threadGroupSize = SCREEN_WIDTH * SCREEN_HEIGHT;
    }
    MTL::Size threadgroupSize = MTL::Size::Make(threadGroupSize, 1, 1);

    computeEncoder->dispatchThreads(gridSize, threadgroupSize);
}

void Engine::encodeViscosityCommand(MTL::ComputeCommandEncoder *computeEncoder) {
    computeEncoder->setComputePipelineState(_mViscosityPSO);
    computeEncoder->setBuffer(particles, 0, 0);

    MTL::Size gridSize = MTL::Size::Make(MAX_PARTICLES, 1, 1);

    NS::UInteger threadGroupSize =
        _mViscosityPSO->maxTotalThreadsPerThreadgroup();
    if (threadGroupSize > MAX_PARTICLES) {
        threadGroupSize = MAX_PARTICLES;
    }
    MTL::Size threadgroupSize = MTL::Size::Make(threadGroupSize, 1, 1);

    computeEncoder->dispatchThreads(gridSize, threadgroupSize);
}