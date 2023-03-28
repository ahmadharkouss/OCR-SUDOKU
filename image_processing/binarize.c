#include "pixel_operations.h"

void grayscale(SDL_Surface* sudok){
  //GrayScale
  
  for (int x =0; x< sudok->w;x++){
    
      for (int y=0;y<sudok->h;y++){
	//For each pixel of the image, do some edits :
	Uint32 pixel = getpixel(sudok, x, y);
        Uint8 r , g , b;
	//Get the pixel, then convert it to its grayscale
       
	SDL_GetRGB(pixel, sudok->format, &r, &g, &b);
        
	Uint32 average=0.3*r + 0.59*g + 0.11*b;
        pixel = SDL_MapRGB(sudok->format, average, average, average); 
        putpixel(sudok, x, y, pixel);
      }
  }
}

//Create an histogram that we use later for Otsu's method
int* create_histogram(SDL_Surface* image)
{
    int* histogram = calloc(256, sizeof(int));
    for (int width = 0; width  < image->w; width++)
    {
        for (int height = 0; height < image->h; height++)
        {
            Uint8 r, g, b;
            Uint32 pixel = getpixel(image, width, height);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            // The image is in grey, so each cell is equal to Red component (which is also equal to Blue's one, Green's one...)
            histogram[r]++;
        }
    }
    return histogram;
}
static int Otsu(SDL_Surface *image)
{
    int threshold = 0;
    double current_max = 0.;
    int sum = 0;
    int sum_background = 0;
    double weight_background = 0; // = Wb
    int nb_pixels = image->h * image->w; //Number of image's pixels

    int *histogram = create_histogram(image);
    for (int i = 0; i < 256; i++)
        sum += i * histogram[i];

    for (int i = 0; i < 256; i++)
    {
        weight_background += histogram[i];
        double weight_foreground = nb_pixels - weight_background; // = Wf
        if (weight_background == 0)
	  continue;
	if( weight_foreground == 0)
          continue;
	//Add each component of one criteria
        sum_background += i * histogram[i];
        int sum_foreground = sum - sum_background;
	
        double mean_background = sum_background / weight_background; // = Mu b
        double mean_foreground = sum_foreground / weight_foreground; // = Mu f
	
	//Variance formula : V = WbWf(Mub-Muf)²
        double variance = weight_background *weight_foreground *(mean_background - mean_foreground)*(mean_background - mean_foreground);
	//Get the Max Variance as possible : It is Otsu's Method.
        if (variance > current_max)
        {
            current_max = variance;
            threshold = i;
        }
	
    }

    free(histogram);

    return threshold;
}

void binarize(SDL_Surface *image)
{
    int threshold = Otsu(image);

    for (int h = 0; h < image->w; h++)
    {
        for (int w = 0; w < image->h; w++)
        {
            Uint8 r, g, b;
            Uint32 pixel = getpixel(image, h, w);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            Uint32 new_pixel;
            if (r > threshold)
                new_pixel = SDL_MapRGB(image->format, 255, 255, 255);
            else
                new_pixel = SDL_MapRGB(image->format, 0, 0, 0);
            putpixel(image, h, w, new_pixel);
        }
    }
}
//brut version to test some things... :)
void binarize2(SDL_Surface *image)
{
    for (int h = 0; h < image->w; h++)
    {
        for (int w = 0; w < image->h; w++)
        {
            Uint8 r, g, b;
            Uint32 pixel = getpixel(image, h, w);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            Uint32 new_pixel;
            if (r > 127)
                new_pixel = SDL_MapRGB(image->format, 255, 255, 255);
            else
                new_pixel = SDL_MapRGB(image->format, 0, 0, 0);
            putpixel(image, h, w, new_pixel);
        }
    }
}
