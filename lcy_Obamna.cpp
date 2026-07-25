#include "lcy_Obamna.h"

SDL_Color GetPixelColor(SDL_Surface *pSurface, const int X, const int Y)
{

    // Bytes per pixel


    /*
  Retrieve the address to a specific pixel
  pSurface->pixels  = an array containing the SDL_Surface pixels
  pSurface->pitch       = the length of a row of pixels (in bytes)
  X and Y               = the offset on where on the image to retrieve the pixel; (0, 0) is the upper left corner
  */
    Uint8 *pPixel = static_cast<Uint8*>(pSurface->pixels) + X * pSurface->pitch + Y * SDL_BYTESPERPIXEL(SDL_PIXELFORMAT_RGBA8888);

    const Uint32 PixelData = *reinterpret_cast<Uint32 *>(pPixel);

    SDL_Color Color = {0u, 0u, 0u, SDL_ALPHA_OPAQUE};

    // Retrieve the RGB values of the specific pixel
    SDL_GetRGB(PixelData, SDL_GetPixelFormatDetails(pSurface->format),SDL_GetSurfacePalette(pSurface), &Color.r, &Color.g, &Color.b);

    return Color;
};

float pixel_pythagoras(SDL_Color colorA, SDL_Color colorB) {
    return (float)(sqrt(pow(colorB.r - colorA.r, 2) + pow(colorB.g - colorA.g, 2) + pow(colorB.b - colorA.b, 2)));
};

float pixel_distance(int sourceX, int sourceY,int dataX, int dataY,SDL_Surface *sourceSurface, SDL_Surface *dataSurface) {
    const float dist=pixel_pythagoras(GetPixelColor(sourceSurface, sourceX, sourceY), GetPixelColor(dataSurface, dataX, dataY));
    return dist;
};

// Created by lucia on 24.07.26.
//