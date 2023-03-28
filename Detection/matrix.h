#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"


typedef struct {
    int rows;
    int cols;
    int * data;
} matrix;

matrix * newMatrix(int rows, int cols);

int deleteMatrix(matrix * mtx);

#define ELEM(mtx, row, col)                     \
    mtx->data[(col-1) * mtx->rows + (row-1)]
    
matrix * copyMatrix(matrix * mtx);
int setElement(matrix * mtx, int row, int col, int val);
int getElement(matrix * mtx, int row, int col, int * val);
matrix * SDLtoMatrix(SDL_Surface *img);
int printMatrix(matrix * mtx);
SDL_Surface * matrixtoSDL(matrix* mtx);
#endif
