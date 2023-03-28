#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

/* Creates a ``rows by cols'' matrix with all values 0.
 * Returns NULL if rows <= 0 or cols <= 0 and otherwise a
 * pointer to the new matrix.
 */

matrix * newMatrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) return NULL;

  // allocate a matrix structure
  matrix * m = (matrix *) malloc(sizeof(matrix));
  // set dimensions
  m->rows = rows;
  m->cols = cols;

  // allocate a double array of length rows * cols
  m->data = (int *) malloc(rows*cols*sizeof(int));
  // set all data to 0
  int i;
  for (i = 0; i < rows*cols; i++)
    m->data[i] = 0.0;

  return m;
}

matrix * SDLtoMatrix(SDL_Surface *img) {
  // allocate a matrix structure
  matrix * m = (matrix *) malloc(sizeof(matrix));
  int cols = img->w;
  int rows = img->h;
  m->rows = rows;
  m->cols = cols;  // allocate a double array of length rows * cols
  m->data = (int *) malloc(rows*cols*sizeof(int));
  // set sdl data
  int i, j;
  Uint32 pixel;
  Uint8 r, g, b;
  for (i = 1; i < cols; i++){
    for (j = 1; j < rows; j++){
      pixel = get_pixel2(img, i ,j);
      SDL_GetRGB(pixel, img->format, &r, &g, &b);
      if(r == 0)
	ELEM(m, j, i) = 1;
      else
	ELEM(m, j, i) = 0;
    }
  }
  return m;
}

SDL_Surface * matrixtoSDL(matrix* mtx){
  int val = 0;
  SDL_Surface* img;
  img = SDL_CreateRGBSurface(0,mtx->cols,mtx->rows,32,0,0,0,0);
  Uint32 pw = SDL_MapRGB(img->format, 255, 255, 255);
  Uint32 pb = SDL_MapRGB(img->format, 0, 0, 0);
  for(int r = 1; r < mtx->rows; r++){
    for(int c = 1; c < mtx->cols; c++){
      val = ELEM(mtx, r, c);
      if(val == 0)
	put_pixel2(img, c, r, pw);
      else
	put_pixel2(img, c, r, pb);
    }
  }
  return img;
}

/* Deletes a matrix.  Returns 0 if successful and -1 if mtx
 * is NULL.
 */
int deleteMatrix(matrix * mtx) {
  if (!mtx) return -1;
  // free mtx's data
  assert (mtx->data);
  free(mtx->data);
  // free mtx itself
  free(mtx);
  return 0;
}

/* Copies a matrix.  Returns NULL if mtx is NULL.
 */
matrix * copyMatrix(matrix * mtx) {
  if (!mtx) return NULL;

  // create a new matrix to hold the copy
  matrix * cp = newMatrix(mtx->rows, mtx->cols);

  // copy mtx's data to cp's data
  memcpy(cp->data, mtx->data,
	 mtx->rows * mtx->cols * sizeof(int));

  return cp;
}

/* Sets the (row, col) element of mtx to val.  Returns 0 if
 * successful, -1 if mtx is NULL, and -2 if row or col are
 * outside of the dimensions of mtx.
 */
int setElement(matrix * mtx, int row, int col, int val){
  if (!mtx) return -1;
  assert (mtx->data);
  if (row <= 0 || row > mtx->rows ||
      col <= 0 || col > mtx->cols)
    return -2;

  ELEM(mtx, row, col) = val;
  return 0;
}

/* Sets the reference val to the value of the (row, col)
 * element of mtx.  Returns 0 if successful, -1 if either
 * mtx or val is NULL, and -2 if row or col are outside of
 * the dimensions of mtx.
 */
int getElement(matrix * mtx, int row, int col,int* val) {
  if (!mtx) return -1;
  assert (mtx->data);
  if (row <= 0 || row > mtx->rows ||
      col <= 0 || col > mtx->cols)
    return -2;
  *val = ELEM(mtx, row, col);
  return 0;
}

/* Prints the matrix to stdout.  Returns 0 if successful
 * and -1 if mtx is NULL.
 */
int printMatrix(matrix * mtx) {
  if (!mtx) return -1;

  int row, col;
  for (row = 1; row <= mtx->rows; row++) {
    for (col = 1; col <= mtx->cols; col++) {
      printf("%d ", ELEM(mtx, row, col));
    }
    // separate rows by newlines
    printf("\n");
  }
  return 0;
}
