#ifndef FILTERS_H_
#define FILTERS_H_

#include "pixel_operations.h"


int truncate1(int a);
void brightness(SDL_Surface *image, int lumi);
void  augmented_brightness(SDL_Surface *image, int n);
//int min(int a , int b);
//int max(int a, int b);
void contrast(SDL_Surface* image, double n);

void higher_contrast(SDL_Surface *image);
void lower_contrast(SDL_Surface *image);


void Filter(SDL_Surface* image,  int divisor);



void blur_filter(SDL_Surface *image, SDL_Surface *ds);
SDL_Surface *mean_blur(SDL_Surface *image, int n);


// unsigned char **CreateCharMatrix(int width, int height);
// int kernel_len(int matrix[]);
#endif
