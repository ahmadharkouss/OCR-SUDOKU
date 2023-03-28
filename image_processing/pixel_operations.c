#include <err.h>
#include "pixel_operations.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

//Operations from the official SDL documentation
static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

//Get the information of a defined pixel at coord's( x,y )
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;
  }
  return 0;
}


//Set the pixel on a defined surface , at coord's ( x , y )
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(Uint16 *)p = pixel;
    break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;
  case 4:
    *(Uint32 *)p = pixel;
    break;
  }
}
/*Pixel new_pixel(Uint8 r, Uint8 g, Uint8 b){
    Pixel pixel;
    pixel.r = r;
    pixel.g = g;
    pixel.b = b;
    return pixel;
}

PixelMatrix *new_pixel_matrix(size_t lines, size_t cols){
    PixelMatrix *matrix;
    matrix = malloc(sizeof(PixelMatrix));
    matrix->lines = lines;
    matrix->cols = cols;
    matrix->data = malloc(lines * cols * sizeof(Pixel));
    return matrix;
}

void free_pixel_matrix(PixelMatrix *matrix){
    free(matrix->data);
    free(matrix);
}
*/

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}



SDL_Surface* copy_image(SDL_Surface *img)
{
  Uint32 pixel;
  SDL_Surface* copy;
  copy = SDL_CreateRGBSurface(SDL_HWSURFACE,
                              img -> w,
                              img -> h,
                              img -> format -> BitsPerPixel,0,0,0,0);
  for(int i = 0; i < img -> w; i++)
    {
      for(int j = 0;j < img -> h; j++)
	{
	  pixel = getpixel(img, i, j);
	  putpixel(copy, i, j, pixel);
	}
    }
  return(copy);
}
//unused
void update_surface(SDL_Surface* screen, SDL_Surface* image)
{
    if (SDL_BlitSurface(image, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    SDL_UpdateRect(screen, 0, 0, image->w, image->h);
}



//Image saving operations
/*
void save_image(SDL_Surface *img, PixelMatrix *image)
{
    Uint8 r, g, b;
    Uint32 pixel;
    for(size_t i = 0; i < image->lines; i++)
        for(size_t j = 0; j < image->cols; j++)
        {
            pixel = getpixel(img, i, j);
            r = (pixel & 0x0000ff00) >> 8;
            g = (pixel & 0x00ff0000) >> 16;
            b = (pixel & 0xff000000) >> 24;
            image->data[i * image->cols + j] = new_pixel(r, g, b);
        }
}

void save_bin(SDL_Surface *img, UnsignedMatrix *image)
{
    Uint32 pixel;
    for(size_t i = 0; i < image->lines; i++)
        for(size_t j = 0; j < image->cols; j++)
        {
            pixel = getpixel(img, i, j);
            if(pixel == 0xffffffff)
              image->data[i * image->cols + j] = 1;
            else
              image->data[i * image->cols + j] = 0;
        }
}
*/
