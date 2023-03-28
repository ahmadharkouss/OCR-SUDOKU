#include <math.h>
#include "pixel_operations.h"


//Min and max Unused (for the moment...)
int min(int a , int b ){
  if(a>b)
    return b;
  return a;
}

int max(int a , int b ){
  if(a<b)
    return b;
  return a;
}

//unused
int kernel_len(int matrix[]){
  int res = 0;
  while(matrix[res] != 0){
    res++;
  }
  return res;
}



//Unused
unsigned char **CreateCharMatrix(int width, int height)
{
	unsigned char **matrix =
		(unsigned char **)malloc(sizeof(unsigned char *) * height);
	for (int i = 0; i < height; i++)
	{
		*(matrix + i) = (unsigned char *)malloc(sizeof(unsigned char) * width);
	}
	return matrix;
}

SDL_Surface *copy_image(SDL_Surface *src, SDL_Surface *dst){
  Uint32 pixel;
  for(int i = 0; i<src->w;i++){
    for(int j = 0; j < src->h; j++){
      pixel = getpixel(src,i , j);
      putpixel(dst,i,j, pixel);
    }
  }
  return dst;
  }

Uint32 ker_sort(Uint32 pixel1, Uint32 pixel2, Uint32 pixel3, Uint32 pixel4, Uint32 pixel5, Uint32 pixel6, Uint32 pixel7,Uint32 pixel8,Uint32 pixel9){
  Uint32 arr[8];
  arr[0] = pixel1;
  arr[1] = pixel2;
  arr[2] = pixel3;
  arr[3] = pixel4;
  arr[4] = pixel5;
  arr[5] = pixel6;
  arr[6] = pixel7;
  arr[7] = pixel8;
  arr[8] = pixel9;
  Uint32 temp = 0;
  for(int i=0;i<9;i++){
    for(int j=i+1;j<9;j++){
      if(arr[i]>arr[j]){
	temp=arr[i];
	arr[i]=arr[j];
	arr[j]=temp;
      }
    }
  }
  return arr;
}



 SDL_Surface* SPG_CopySurface(SDL_Surface* src)
{
  return SDL_ConvertSurface(src, src->format, SDL_SWSURFACE);
  }
