/*
    * Interpolation.h
    *
    *  Created on: 2023. 11. 05.
    *  Author: Jiwoon Lee
    * 
*/

#include <stdint.h>

#ifndef INTERPOLATION_H
#define INTERPOLATION_H

// Using static const for better type checking and scoping
static const int WIDTH = 128;
static const int HEIGHT = 128;
static const int EXT_WIDTH = 512;
static const int EXT_HEIGHT = 512;
static const int SCALE = 4;
static const int PHASE = 1;

typedef struct Image {
    uint8_t** inputBuffer;
    uint8_t** outputBuffer;
} Image;

typedef struct Interpolation {
    int** tempImage;
    uint8_t** scaleMap;
} Interpolation;

void NearestNeighborInterpolation(Interpolation* interpolation, Image* image);
void BilinearInterpolation(Interpolation* interpolation, Image* image);
void BicubicInterpolation(Interpolation* interpolation, Image* image);
void SixtabInterpolation(Interpolation* interpolation, Image* image);
void replicatePhaseShift(Image* image);

#endif // !INTERPOLATION_H
