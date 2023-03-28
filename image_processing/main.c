#include <err.h>
#include "SDL/SDL.h"
#include "SDL_rotozoom.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "binarize.h"
#include "filters.h"
#include "display.h"

/*
SDL_Surface *image_treatment(char *path, int contrast_value, int brightness_value, int blur, int angle){
  SDL_Surface *image = IMG_Load(path);
  mean_blur(image, blur);
  contrast (image, contrast_value);
  brightness (image, brightness_value );
  binarize(image);
  rotate(image,angle);
  return image;
}

*/
int main(int argc, char *argv[])
{
  //1 filename
  SDL_Surface *image = IMG_Load(argv[1]);
  
  //2 lumi
  brightness (image, atoi(argv[2]) );
  
  //3 contrast
  contrast (image,atof(argv[3]));

  //4 blur
  mean_blur(image, atoi(argv[4]));
    
  binarize(image);
  //5 angle
  double angle = atof(argv[5]);
  if (angle ==0)
    display1(image);
  else{
    SDL_Surface *rotation = NULL;
    SDL_Rect position;
    position.x =0;
    position.y = 0;
    //Create SDL Interface
    SDL_Surface *window = NULL;
    //Ask directly to the GPU to create an area that has its specs
    window = SDL_SetVideoMode(1700,1000,32,SDL_HWSURFACE);
    //"create a white rectangle that fills ALL area
    SDL_FillRect (window, NULL, SDL_MapRGB(window->format, 255,255,255));
    //update the area
    SDL_Flip(window);
   
    rotation = rotozoomSurface(image, angle, 1.0, 1);
    //On transforme la surface image.
 
    //On positionne l'image en fonction de sa taille.
    if(angle == 35)
      {
	position.x = -280;
	position.y = -480;
     
      }
    SDL_BlitSurface(rotation , NULL, window, &position);
    SDL_Flip(window);
    SDL_Flip(rotation);
    while(42){
        
      //To quit :
      SDL_Event red_cross;
      SDL_WaitEvent(&red_cross);
      //red cross for ubuntu
      if(red_cross.type == SDL_QUIT){
	break;
      }
      // keydown to use on Archlinux
      if(red_cross.type == SDL_KEYDOWN){
        if(red_cross.key.keysym.sym == SDLK_DOWN){
	  break;
        }
      }
    }
    SDL_FreeSurface(rotation);
  }
 
  return 0;
}
 
