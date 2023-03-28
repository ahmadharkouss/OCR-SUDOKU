#include "pixel_operations.h"
#include "binarize.h"
#include <math.h>

//Filters.c :
//min function
int min(int a , int b ){
  if(a>b)
    return b;
  return a;
}
//max function
int max(int a , int b ){
  if(a<b)
    return b;
  return a;
}

//This function avoid over-saturation of a pixel
//8bits : can not go beyond 255 (and vice-versa <0)
int truncate1(int a){
  if(a<0)
    return 0;
  if(a>255)
    return 255;
  else
    return a;
}

//brightness filter
void brightness(SDL_Surface *image, int lumi) {
   for (int x =0; x< image->w;x++){
    
      for (int y=0;y<image->h;y++){
	//For each pixel of the image, do some edits :
	Uint32 pixel = getpixel(image, x, y);
        Uint8 r , g , b;
	//Here 'edits' = add or substract arg(lumi) given
	SDL_GetRGB(pixel, image->format, &r, &g, &b);
        r+= lumi;
	g+= lumi;
	b+= lumi;
        pixel = SDL_MapRGB(image->format, truncate1(r), truncate1(g),truncate1(b)); 
        putpixel(image, x, y, pixel);
      }
  }
}
//does not work
/* void conconcontrast1(SDL_Surface *image, int contra){ */
/*     Uint32 pixel; */
/*     Uint8 r,g,b; */
/*     for (int x =0; x< image->w;x++){ */
/*         for (int y=0;y<image->h;y++){ */
/*             //For each pixel of the image, do some edits : */
/*             pixel = getpixel(image, x, y); */
/*             //'edits' = add or substract arg(lumi) given */
/*             SDL_GetRGB(pixel, image->format, &r, &g, &b); */
/*             //Edits = double components values */
/*             pixel = SDL_MapRGB(image->format, truncate1(r*contra), truncate1(g*contra),truncate1(b*contra));  */
/*             putpixel(image, x, y, pixel); */
/*         } */
/*     } */
/* } */
Uint8 feli(Uint8 c, double n)
{
    if(c <= 255 / 2)
        return (Uint8)( (255/2) * pow((double) 2 * c / 255, n));
    else
        return 255 - feli(255 - c, n);
}
//not used
void contrast(SDL_Surface *image, double n){
    Uint32 pixel;
    Uint8 r,g,b;
    for (int x =0; x< image->w;x++){
        for (int y=0;y<image->h;y++){
            pixel = getpixel(image,x,y);
            SDL_GetRGB(pixel,image->format, &r, &g, &b);
            
            r = feli(r,n);
            g = feli(g,n);
            b = feli(b,n);
            pixel = SDL_MapRGB(image->format,r,g,b);
            putpixel(image,x,y,pixel);
        }
    }
}
//same functions but with simplified steps
//in case of user's laziness :)
void higher_contrast(SDL_Surface *image){
   for (int x =0; x< image->w;x++){
    
      for (int y=0;y<image->h;y++){
	//For each pixel of the image, do some edits :
	Uint32 pixel = getpixel(image, x, y);
        Uint8 r , g , b;
	//'edits' = add or substract arg(lumi) given
	SDL_GetRGB(pixel, image->format, &r, &g, &b);
        //Edits = double components values
        pixel = SDL_MapRGB(image->format, truncate1(r*2), truncate1(g*2),truncate1(b*2)); 
        putpixel(image, x, y, pixel);
      }
  }
}

void lower_contrast(SDL_Surface *image){
   for (int x =0; x< image->w;x++){
    
      for (int y=0;y<image->h;y++){
	//For each pixel of the image, do some edits :
	Uint32 pixel = getpixel(image, x, y);
        Uint8 r , g , b;
	//'edits' = add or substract arg(lumi) given
	SDL_GetRGB(pixel, image->format, &r, &g, &b);
        //Edits = double components values
        pixel = SDL_MapRGB(image->format, truncate1(r/2), truncate1(g/2),truncate1(b/2)); 
        putpixel(image, x, y, pixel);
      }
  }
}

//function used to edit contrast
Uint8 pow_truncate(Uint8 c, int n)
{
    return (Uint8) (255 * pow((double) c / 255, n));
}
//the one used
//contrast filter
void  augmented_brightness(SDL_Surface *image, int n){
  Uint32 pixels;
  Uint8 r,g,b;
  for(int i = 0; i < image->h; i++)
    {
      for(int j = 0; j < image->w; j++)
	{

	  //for each pixel, use the function above
	  SDL_GetRGB(pixels, image->format, &r, &g, &b);
	  r = pow_truncate(r, n);
	  g = pow_truncate(g, n);
	  b = pow_truncate(b, n);
	  pixels = SDL_MapRGB(image->format, r, g, b);
	  putpixel(image,i,j,pixels);
	}
    }
}



 //Does not work ... idk why , took me 2 weeks of my life :)
void blur_filter(SDL_Surface *image,SDL_Surface *res)
{
    int w =  image->w;
    int h = image-> h;
    /*res = SDL_ConvertSurface(image,image->format, SDL_SWSURFACE);
      res = SPG_CopySurface(image);*/
    //res = SDL_CreateRGBSurface(0, w, h, 32, 255, 255, 255, 0x000000ff);
    //  grayscale(image);
    //Uint32 acc;
    for(int i = 10 ; i < w-10; i++){
        for(int j = 10; j < h-10; j++){
     
            Uint32 pixel1 = getpixel(image, i-1, j-1);
            Uint8 r1, g1, b1;
            SDL_GetRGB(pixel1, image->format, &r1, &g1, &b1);
            pixel1 = SDL_MapRGB(image->format, r1, g1, b1);
      
            Uint32 pixel2 = getpixel(image, i-1, j);
            Uint8 r2, g2, b2;
            SDL_GetRGB(pixel2, image->format, &r2, &g2, &b2);
            pixel2 = SDL_MapRGB(image->format, r2, g2, b2);
      
            Uint32 pixel3 = getpixel(image, i-1, j+1);
            Uint8 r3, g3, b3;
            SDL_GetRGB(pixel3, image->format, &r3, &g3, &b3);
            pixel3 = SDL_MapRGB(image->format, r3, g3, b3);
      
            //middle row
            Uint32 pixel4 = getpixel(image, i, j-1);
            Uint8 r4, g4, b4;
            SDL_GetRGB(pixel4, image->format, &r4, &g4, &b4);
            pixel4 = SDL_MapRGB(image->format, r4, g4, b4);
      
            Uint32 pixel5 = getpixel(image, i, j);
            Uint8 r5, g5, b5;
            SDL_GetRGB(pixel5, image->format, &r5, &g5, &b5);
            pixel5 = SDL_MapRGB(image->format, r5, g5, b5);
     
            Uint32 pixel6 = getpixel(image, i, j+1);
            Uint8 r6, g6, b6;
            SDL_GetRGB(pixel6, image->format, &r6, &g6, &b6);
            pixel6 = SDL_MapRGB(image->format, r6, g6, b6);

            //bottom row
            Uint32 pixel7 = getpixel(image, i+1, j-1);

            Uint8 r7, g7, b7;
            SDL_GetRGB(pixel7, image->format, &r7, &g7, &b7);
            pixel7 = SDL_MapRGB(image->format, r7, g7, b7);

            Uint32 pixel8 = getpixel(image, i+1, j);
            Uint8 r8, g8, b8;
            SDL_GetRGB(pixel8, image->format, &r8, &g8, &b8);
            pixel8 = SDL_MapRGB(image->format, r8, g8, b8);
      
            Uint32 pixel9 = getpixel(image, i+1, j+1);
            Uint8 r9, g9, b9;
            SDL_GetRGB(pixel9, image->format, &r9, &g9, &b9);
            pixel6 = SDL_MapRGB(image->format, r9, g9, b9);
      
            Uint32 a =(pixel1 +pixel2 + pixel3 + pixel4 + pixel5 + pixel6 + pixel7 + pixel8 + pixel9)/9;
            //Uint32 arr[8] = ker_sort( pixel1,  pixel2,  pixel3,  pixel4,  pixel5,  pixel6,  pixel7, pixel8, pixel9);
            putpixel(res, i, j,a/9) ;
        }

    }
}

//i for rows, j for cols
Uint32 moyenne(SDL_Surface *surface, int i, int j, int n)
 {
     int initial_h = max(i - n, 0);
     int initial_w = max(j - n, 0);
     int final_h = min(i + n, surface->h - 1);
     int final_w = min(j + n, surface->w - 1);
     int nb_pixel = ((final_h - initial_h) * (final_w - initial_w));
    

     Uint32 sum_r = 0, sum_g = 0, sum_b = 0;
     Uint8 r,g,b;

     for ( i = initial_w; i < final_w; i++)
         for( j = initial_h; j < final_h; j++)
         {
             Uint32 p = getpixel(surface, i , j);
             SDL_GetRGB(p, surface->format, &r, &g, &b);
             sum_r += r;
             sum_g += g;
             sum_b += b;
         }
     //if(nb_pixel < 1)
     //  return 0;
     return SDL_MapRGB(surface->format, sum_r / nb_pixel, sum_g / nb_pixel, sum_b / nb_pixel);
 }

//final version which works but so sad
//n is the parameter which set the blur effect
///the greater it is, the blurriest the image wil be
SDL_Surface *mean_blur(SDL_Surface* image, int n) {
  if ( n == 0 )
    return image;
  else{
    for(int i = 0  ; i < image->w; i++) {
      for(int j = 0; j < image->h; j++){
	Uint32 pixel = moyenne(image,j,i,n);
	putpixel(image, i , j , pixel );
      }
    }
  }
  return image;
}

