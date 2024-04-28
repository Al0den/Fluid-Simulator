# Fluid Simulation

This is a storing repository, for a test at making a particle based fluid simulation. It uses Apple's Metal API, and was only tested on Apple Silicon

Far from achieving anything, it is more of a personal interest at physics simulators rather than a realistic one.

## How to run

First, generate the Makefile using `cmake . && make .` to generate the executables. The Metal CPP files are already included inside `./src/Metal` and `./src/Foundation`

Then, simply run `./physics` to get inside the simulation

## Controls

Currently, the only available controls are:
- `CTRL` Creates a pull effect
- `L-SHIFT` Creates a repelleing effect 
- `SPACE` Teleports particle to the top left of the screen

All of them happen on the mouse

All the settings can be found at `./src/settings.h`

## Screenshots

<p align="center">
The repel effect in motion
</p>

<p align="center">
  <img src="https://github.com/Al0den/Fluid-Simulator/assets/111601320/af0155f2-7a15-425d-b853-f7fe34cb80dc">
</p>

<p align="center">
Initial start distribution example
</p>

<p align="center">
    <img src="https://github.com/Al0den/Fluid-Simulator/assets/111601320/233eea58-7640-4d65-8054-1a394ba2eaaf">
</p>


