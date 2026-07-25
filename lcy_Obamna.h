//
// Created by lucia on 24.07.26.
//

#ifndef OBAMNA_LCY_OBAMNA_H
#define OBAMNA_LCY_OBAMNA_H
#include <SDL3/SDL.h>
#include <cmath>

SDL_Color GetPixelColor(SDL_Surface *pSurface,  int X,  int Y);
float pixel_pythagoras(SDL_Color colorA, SDL_Color colorB);
float pixel_distance(int sourceX, int sourceY,int dataX, int dataY,SDL_Surface *sourceSurface, SDL_Surface *dataSurface);
#endif //OBAMNA_LCY_OBAMNA_H