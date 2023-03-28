#ifndef _CUT_H_
#define _CUT_H_

#include "matrix.h"
#include "rlsa.h"
#include "display.h"

matrix * cutGraph(SDL_Surface* img);
int label(matrix* mtx, matrix* connexe);
void cutMatrix(matrix * mtx, SDL_Surface *array[81]);
int * cutCol(matrix * mtx);
int * cutRow(matrix * mtx);
#endif
