/*
    * Interpolation.c
    *
    *  Created on: 2023. 11. 05.
    *  Author: Jiwoon Lee
    * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "Interpolation.h"
#include "utils.h"

/**
 * @brief Performs bilinear interpolation.
 */
void BilinearInterpolation(Interpolation* interpolation, Image* image) {
    uint16_t virtualBoundary = EXT_WIDTH - SCALE;
    allocateInterpolation(interpolation, EXT_WIDTH);
    for (int h = 0; h < image->width; h++) {
        for (int w = 0; w < image->width; w++) {
            interpolation->tempBuffer[h * SCALE][w * SCALE] = (uint16_t)image->inputBuffer[h][w];
        }
    }

    for (int h = 0; h < EXT_WIDTH; h += SCALE) {
        for (int w = 0; w < EXT_WIDTH; w += SCALE) {
            if (w < virtualBoundary) {
                for (int k = 1; k < SCALE; k++) {
                    interpolation->tempBuffer[h][w + k] = ((SCALE - k) * interpolation->tempBuffer[h][w]) + (k * interpolation->tempBuffer[h][w + SCALE]);
                    interpolation->scaleMap[h][w + k] = 1;
                }
            }
            interpolation->tempBuffer[h][w] *= SCALE;
            interpolation->scaleMap[h][w] = 1;
        }
    }

    for (int w = 0; w < virtualBoundary + 1; w++) {
        for (int h = 0; h < virtualBoundary; h += SCALE) {
            for (int k = 1; k < SCALE; k++) {
                interpolation->tempBuffer[h + k][w] = ((SCALE - k) * interpolation->tempBuffer[h][w]) + (k * interpolation->tempBuffer[h + SCALE][w]);
                interpolation->scaleMap[h + k][w] = 2;
            }
        }
    }

    for (int h = 0; h < virtualBoundary + 1; h++) {
        for (int w = 0; w < virtualBoundary + 1; w++) {
            image->outputBuffer[h][w] = roundingOff(interpolation->tempBuffer[h][w], SCALE, interpolation->scaleMap[h][w]);
        }
    }

    for (int w = virtualBoundary + 1; w < EXT_WIDTH; w++) {
        for (int h = 0; h < virtualBoundary + 1; h++) {
            image->outputBuffer[h][w] = image->outputBuffer[h][virtualBoundary];
            image->outputBuffer[w][h] = image->outputBuffer[virtualBoundary][h];
        }
    }
    for (int h = virtualBoundary + 1; h < EXT_WIDTH; h++) {
        for (int w = virtualBoundary + 1; w < EXT_WIDTH; w++) {
            image->outputBuffer[h][w] = image->inputBuffer[image->width - 1][image->width - 1];
        }
    }
    deleteInterpolation(interpolation, EXT_WIDTH);
}
