#ifndef BINARIZE_H_
#define BINARIZE_H_

#include "pixel_operations.h"
void grayscale(SDL_Surface* surface);
int* create_histogram(SDL_Surface* image);
int Otsu(SDL_Surface* image);
void binarize(SDL_Surface* image);
void binarize2(SDL_Surface* image);
#endif
