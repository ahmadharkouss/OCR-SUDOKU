#include "cut.h"

matrix * cutGraph(SDL_Surface* img){
  SDL_Surface * rlsaimg = copy_image2(img);
  rlsa(rlsaimg);
  matrix * mat = SDLtoMatrix(img);
  matrix * mtx = SDLtoMatrix(rlsaimg);
  matrix * connexe = newMatrix(mtx->rows, mtx->cols);
  int lab = label(mtx, connexe);
  int array[lab];
  for(int k = 0; k < lab; k++)
    array[k] = 0;
  for(int i = 1; i < mtx->rows; i++){
    for(int j = 1; j < mtx->cols; j++){
      if(ELEM(connexe, i, j) != 0)
	array[ELEM(connexe, i, j)] += 1;
    }
  }
  int max = array[0];
  int num = 0;

  for(int i = 1; i < lab; i++){
    if(array[i] > max){
      num = i;
      max = array[i];
    }
  }

  int val;
  
  for(int x = 1; x < mtx->rows; x++){
    for(int y = 1; y < mtx->cols; y++){
      val = ELEM(connexe, x, y);
      if(val != num)
	  ELEM(mat, x, y) = 0;
      }
    } 

  deleteMatrix(mtx);
  return mat;
  
}

int label(matrix* mtx, matrix* connexe){
  int label = 0, l = 0;
  int dx[5] = {1,1,0,-1,-1};
  int dy[5] = {0,1,1,1,0};
  for(int i = 1; i < mtx->rows; i++){
    for(int j = 1; j < mtx->cols; j++){
      if(ELEM(mtx, i, j) == 1){

	if(ELEM(connexe, i, j) != 0)
	  l = ELEM(connexe, i, j);
	else{
	  label += 1;
	  l = label;
	  ELEM(connexe, i, j) = l;
	}
	for(int x = 0; x < 5; x++){
	  //test if in range
	  if(i + dy[x] > mtx->rows || j + dx[x] > mtx->cols)
	    continue;
	  if(ELEM(connexe,i + dy[x], j + dx[x]) != 0)
	    continue;
	  if(ELEM(mtx,i + dy[x], j + dx[x]) == 1)
	    ELEM(connexe, i + dy[x], j + dx[x]) = l;
	}
      }
    }
  }
  return label;
}

void cutMatrix(matrix * mtx, SDL_Surface *array[81]){
  
  int* col =(int *) malloc(18 * sizeof(int));
  int* row =(int *) malloc(18 * sizeof(int));
  col = cutCol(mtx);
  row = cutRow(mtx);
  int x, y, i, j, val;
  Uint32  pb, pw;
  //each box
  for(j = 0; j < 9; j++){
    for(i = 0; i < 9; i++){
      SDL_Surface * box =
	SDL_CreateRGBSurface(0, col[2*i+1]-col[2*i], row[2*j+1]-row[2*j],32,255,255,255,0);
      pb = SDL_MapRGB(box->format, 0, 0, 0);
      pw = SDL_MapRGB(box->format, 255, 255, 255);
      //each pixel in the case
      for(x = col[2*i]; x < col[2*i+1]; x++){
	for(y = row[2*j]; y < row[2*j+1]; y++){
	  val = ELEM(mtx, y+1, x+1);
	  if(val == 1)
	    put_pixel2(box, x - col[2*i], y - row[2*j], pb);
	  else
	    put_pixel2(box, x - col[2*i], y - row[2*j], pw);
	}
      }

      array[j*9 + i] = box;
    }
  }
  free(col);
  free(row);
}

int* cutCol(matrix * mtx){
  int y, x;
  int val = 0;
  long nbb = 0;
  int *hor = (int *)malloc(mtx->cols * sizeof(int));
  //put in the array the number of black pixels in each cols
  for(y = 0; y < mtx->cols; y++){
    for(x = 0; x < mtx->rows; x++){
      val = ELEM(mtx, x+1, y+1);
      nbb += (long)val;
    }
    hor[y] = nbb;
    nbb = 0;
  }
  //put the coordinate of each case in another array
  int* chor =(int *) malloc(18 * sizeof(int));
  long j = 2 ,i, b = 0;
  for(i = 0; i<9; i++){
    while(b == 0){
      if(3*hor[j] < hor[j-1]){
	chor[2*i] = j;
	b = 1;
      }
      j++;
    }
    b = 0;
    while(b == 0){
      if(hor[j] > 3*hor[j-1]){
	chor[2*i+1] = j;
	b = 1;
      }
      j++;
    }
    b = 0;
  }
  free(hor);
  return chor;
}

int* cutRow(matrix * mtx){
  int y, x;
  int val = 0;
  long nbb = 0;
  int *ver = (int *)malloc(mtx->rows * sizeof(int));
  //put in the array the number of black pixels in each cols
  for(y = 0; y < mtx->rows; y++){
    for(x = 0; x < mtx->cols; x++){
      val = ELEM(mtx, x+1, y+1);
      nbb += (long)val;
    }
    ver[y] = nbb;
    nbb = 0;
  }
  //put the coordinate of each case in another array
  int* cver =(int *) malloc(18 * sizeof(int));
  long j = 2 ,i, b = 0;
  for(i = 0; i<9; i++){
    while(b == 0){
      if(3*ver[j] < ver[j-1]){
	cver[2*i] = j;
	b = 1;
      }
      j++;
    }
    b = 0;
    while(b == 0){
      if(ver[j] > 3*ver[j-1]){
	cver[2*i+1] = j;
	b = 1;
      }
      j++;
    }
    b = 0;
  }
  free(ver);
  return cver;
}
