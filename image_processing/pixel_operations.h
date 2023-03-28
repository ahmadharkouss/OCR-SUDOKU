#ifndef PIXEL_OPERATIONS_H_
#define PIXEL_OPERATIONS_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

void update_surface(SDL_Surface* screen, SDL_Surface* image);
SDL_Surface* load_image(char *path);

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
SDL_Surface* copy_image(SDL_Surface *img);
void wait_for_keypressed();
SDL_Surface* display_image(SDL_Surface *img);

#endif
