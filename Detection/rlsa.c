#include "rlsa.h"

void rlsa(SDL_Surface *img)
{
    int *ver = ver_rlsa(img);
    int *hor = hor_rlsa(img);
    for(int i = 0; i < img->w; i++)
    {
        for(int j = 0; j < img->h; j++)
        {
            Uint8 rgb;
            if(ver[i + j * img->w] == 0 && hor[i + j * img->w] == 0)
                rgb = 0;
            else
                rgb = 255;
            Uint32 pixel = SDL_MapRGB(img->format, rgb, rgb, rgb);
            put_pixel2(img, i, j, pixel);
        }
    }

    free(hor);
    free(ver);
}

int *ver_rlsa(SDL_Surface *img)
{
    Uint32 pixel;
    Uint8 r, g, b;

    int *ver;
    ver = malloc(sizeof(int) * img->w * img->h);
    for(int i = 0; i < img->w; i++)
    {
        int count = 0;
        for(int j = 0; j < img->h; j++)
        {
            pixel = get_pixel2(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            ver[i + j * img->w] = r;
            if(r == 0)
            {
                if(count <= img->h/3)
                    for(int k = j; k >= j - count; k--)
                        ver[i + k * img->w] = 0;
                count = 0;
            }
            else
                count++;
        }
    }
    return ver;
}

int *hor_rlsa(SDL_Surface *img)
{
    Uint32 pixel;
    Uint8 r, g, b;

    int *hor;
    hor = malloc(sizeof(int) * img->w * img->h);
    for(int j = 0; j < img->h; j++)
    {
        int count = 0;
        for(int i = 0; i < img->w; i++)
        {
            pixel = get_pixel2(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            hor[i + j * img->w] = r;
            if(r == 0)
            {
                if(count <= img->w/3)
                    for(int k = i; k >= i - count; k--)
                        hor[k + j * img->w] = 0;
                count = 0;
            }
            else
                count++;
        }
    }
    return hor;
}
