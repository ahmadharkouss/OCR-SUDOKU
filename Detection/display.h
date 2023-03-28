#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void init_sdl2();
SDL_Surface* load_image2(char *path);
SDL_Surface* display_image2(SDL_Surface *img);
SDL_Surface* copy_image2(SDL_Surface *img);
void wait_for_keypressed2();
Uint32 get_pixel2(SDL_Surface *surface, unsigned x, unsigned y);
void put_pixel2(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void update_surface2(SDL_Surface* screen, SDL_Surface* image);
#endif
