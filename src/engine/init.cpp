#include "engine.h"

void Engine::init(MTL::Device *device) {
    _mDevice = device;

    NS::Error *error = nullptr;

    NS::String *path =
        NS::String::string("shaders.metallib", NS::UTF8StringEncoding);
    MTL::Library *defaultLibrary = device->newLibrary(path, &error);

    auto particle_str = NS::String::string("ParticleStep", NS::ASCIIStringEncoding);
    auto density_str = NS::String::string("DensityMapUpdate", NS::ASCIIStringEncoding);
    auto gradient_str = NS::String::string("GradientMapUpdate", NS::ASCIIStringEncoding);
    auto density_coeff_str = NS::String::string("DensityCoeffInit", NS::ASCIIStringEncoding);
   
    MTL::Function *addFunction = defaultLibrary->newFunction(particle_str);
    MTL::Function *updateDensityMapFunction = defaultLibrary->newFunction(density_str);
    MTL::Function *calculateGradientFunction = defaultLibrary->newFunction(gradient_str);
    MTL::Function *densityCoeffStr = defaultLibrary->newFunction(density_coeff_str);
   
    defaultLibrary->release();

    if (addFunction == nullptr || updateDensityMapFunction == nullptr || calculateGradientFunction == nullptr || densityCoeffStr == nullptr ) {
        std::cout << "Failed to find one of the functions." << std::endl;
        return;
    }

    // Create a compute pipeline state object.
    _mAddFunctionPSO = _mDevice->newComputePipelineState(addFunction, &error);
    _mDensityMapUpdaterPSO = _mDevice->newComputePipelineState(updateDensityMapFunction, &error);
    _mGradientCalculatorPSO = _mDevice->newComputePipelineState(calculateGradientFunction, &error);
    _mDensityCoeffPSO = _mDevice->newComputePipelineState(densityCoeffStr, &error);
    
    addFunction->release();
    updateDensityMapFunction->release();
    calculateGradientFunction->release();
    densityCoeffStr->release();
   
    if (_mAddFunctionPSO == nullptr || _mDensityMapUpdaterPSO == nullptr || _mGradientCalculatorPSO == nullptr || _mDensityCoeffPSO == nullptr) {
        std::cout << "Failed to created pipeline state object, error " << error
                  << "." << std::endl;
        return;
    }

    _mCommandQueue = _mDevice->newCommandQueue();
    if (_mCommandQueue == nullptr) {
        std::cout << "Failed to find the command queue." << std::endl;
        return;
    }
    
    this->init_particles();
    this->init_density_map();
    this->init_gradient_buffers();
    this->init_mouse_data();
    this->init_density_coeffs();

    this->minimum_density = 0;
    this->maximum_density = 0;

    printf("Engine initialized.\n");

    this->steps = 0;
}

void Engine::init_density_coeffs() {
    this->density_coeffs = _mDevice->newBuffer(sizeof(float) * WIDTH * HEIGHT, MTL::ResourceStorageModeShared);

    MTL::CommandBuffer *commandBuffer = _mCommandQueue->commandBuffer();
    MTL::ComputeCommandEncoder *computeEncoder = commandBuffer->computeCommandEncoder();
    
    encodeDensityCoeffCommand(computeEncoder);

    computeEncoder->endEncoding();
    commandBuffer->commit();
    commandBuffer->waitUntilCompleted();

    this->density_coeffs->didModifyRange(NS::Range::Make(0, sizeof(float) * WIDTH * HEIGHT));
}

void Engine::init_mouse_data() {
    this->mouseData = _mDevice->newBuffer(sizeof(int) * 4, MTL::ResourceStorageModeShared);
    int* mouseData = (int*)this->mouseData->contents();
    mouseData[0] = 0;
    mouseData[1] = 0;
}

void Engine::init_gradient_buffers() {
    this->gradientX = _mDevice->newBuffer(sizeof(float) * WIDTH * HEIGHT, MTL::ResourceStorageModeShared);
    this->gradientY = _mDevice->newBuffer(sizeof(float) * WIDTH * HEIGHT, MTL::ResourceStorageModeShared);
    this->clear_gradient_buffers();
}

void Engine::init_particles() {
    this->particles = _mDevice->newBuffer(sizeof(Particle) * MAX_PARTICLES, MTL::ResourceStorageModeShared);
    Particle* particles = (Particle*)this->particles->contents();
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].init(i);
    }
}

void Engine::init_density_map() {
    this->density_map = _mDevice->newBuffer(sizeof(float) * WIDTH * HEIGHT, MTL::ResourceStorageModeShared);
    this->clear_density_map();
}