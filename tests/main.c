//#include <gtk/gtk.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>
#include <string.h>
#include "../image_processing/display.h"
#include "../image_processing/pixel_operations.h"

#include "../image_processing/SDL_rotozoom.h"
#include "../image_processing/binarize.h"
#include "../image_processing/filters.h"
#include "../image_processing/rotate.h"



#include "../test_NN/softmax.h"
#include "../training_NN/relu.h"

#include "../Detection/rlsa.h"
#include "../Detection/cut.h"
#include "../Detection/matrix.h"

//David's part

SDL_Surface *image_treatment(char *path){
    SDL_Surface *image = IMG_Load(path);
    binarize(image);
    return image;
}

//FELIX PART 


void sudoku_detection(SDL_Surface * img, SDL_Surface * array[81]){
  //find the sudoku
  //matrix* mtx = cutGraph(img);
  matrix* mtx = SDLtoMatrix(img);
  //find sudoku blocks
  cutMatrix(mtx, array);
  matrix * arrmtx[81];
  for(int i = 0; i < 81; i++){
    array[i] = rotozoomSurface(array[i], 0.0, 28.0/(double)array[i]->w, 1.0);
  }
  
  deleteMatrix(mtx);
}

//PARAMETER:
//surfaces: all the cut squares of the sudoku
void digit_recognition(SDL_Surface* surfaces[81] , int *array){
    int numHidden = 100;
    int numOutputs = 10;
    //CREATES THE ARRAYS WE NEED
    int labels[81];
    double hidden1[numHidden];
    double hidden2[numHidden];
    double outputs[numOutputs];
    double hiddenWeights1[numHidden][784];
    double hiddenBiases1[numHidden];
    double hiddenWeights2[numHidden][numHidden];
    double hiddenBiases2[numHidden];
    double outputWeights[numOutputs][numHidden];
    double outputBiases[numOutputs];

    //INITIALISES WEIGHTS AND BIASES FROM A FILE
    FILE* file = NULL;
    file = fopen("../param_NN.txt", "r");
    if(file == NULL){
        printf("Error: cannot open file \"param_NN.txt\"\n");
    }
    else{
        for (int i = 0; i < numHidden; ++i) {
            fscanf(file, "%lf\n", &hiddenBiases1[i]);
            for (int j = 0; j < 784; ++j) {
                fscanf(file, "%lf\n", &hiddenWeights1[i][j]);
            }
        }
        for (int i = 0; i < numHidden; ++i) {
            fscanf(file, "%lf\n", &hiddenBiases2[i]);
            for (int j = 0; j < numHidden; ++j) {
                fscanf(file, "%lf\n", &hiddenWeights2[i][j]);
            }
        }
        for (int i = 0; i < numOutputs; ++i) {
            fscanf(file, "%lf\n", &outputBiases[i]);
            for (int j = 0; j < numHidden; ++j) {
                fscanf(file, "%lf\n", &outputWeights[i][j]);
            }
        }
        fclose(file);
        printf("Weights and biases have been loaded succesfully from \"param_NN.txt\"\n");
    }

    //CYCLES THROUGH EACH SURFACE OF THE SUDOKU
    for (int i = 0; i < 81; ++i) {
        //INITIALISES THE INPUTS ARRAY
        int inputs[784];
        Uint8 r,g,b;
        for (int j = 0; j < 28; ++j) {
            for (int k = 0; k < 28; ++k) {
                Uint32 pixel = getpixel(surfaces[i], j, k);
                SDL_GetRGB(pixel, surfaces[i]->format, &r,&g,&b);
                if (r == 0){
                    inputs[k*28+j] = 1;
                }
                else{
                    inputs[k*28+j] = 0;
                }
            }
        }

        for (int j = 0; j < 28; ++j) {
            for (int k = 0; k < 28; ++k) {
                printf("%i ", inputs[j*28+k]);
            }
            printf("\n");
        }
        printf("\n");

        //----------FORWARD PROPAGATION----------

        //HIDDEN LAYER 1
        for (int j=0; j<numHidden; j++) {
            double activation = hiddenBiases1[j];
            for (int k=0; k<784; k++) {
                activation += inputs[k]*hiddenWeights1[j][k];
            }
            hidden1[j] = relu(activation);
        }

        //HIDDEN LAYER 2
        for (int j=0; j<numHidden; j++) {
            double activation = hiddenBiases2[j];
            for (int k=0; k<numHidden; k++) {
                activation+=hidden1[k] * hiddenWeights2[j][k];
            }
            hidden2[j] = relu(activation);
        }

        //OUTPUT LAYER
        for (int j=0; j<numOutputs; j++) {
            double activation = outputBiases[j];
            for (int k=0; k<numHidden; k++) {
                activation+=hidden2[k] * outputWeights[j][k];
            }
            outputs[j] = activation;
        }
        softmax(outputs, numOutputs);

        //DEFINES THE FINAL HYPOTHESIS
        double higherProbability = 0.0;
        int hypothesis;
        for (int j = 0; j < numOutputs; ++j) {
            if(outputs[j] > higherProbability){
                higherProbability = outputs[j];
                hypothesis = j;
            }
        }
        //INITIALISES THE CORRESPONDING LABEL
        labels[i] = hypothesis;
    }
    int *label_pointer = &labels[0];

    for(int i=0 ; i <81 ; ++i)
        *(array +i) =*(label_pointer + i);

}


//copy 2 arrays : external function used in solver
void copy_arrays_pointers(int *begin,  int *begin2){
    for (int  i = 0; i < 81; i++)
             *(begin2 + i)  =  *(begin + i) ;
}



//solver:

//check if the position is safe for  value n  with coordiante x and y in the grid
int safe_pointers(size_t y , size_t x , int n , int *array,size_t len) 
{
    //testing if a row contain n 
    for(size_t i=0 ;i<len ; i++){
        if (array[y*9+i]==n){
            return 0;
        }
    }
    //testing if a column contain n 
    for(size_t j=0 ;j<len ; j++){
        if (array[j*9 + x]==n){
            return 0;
        }
    }
    //testing inside the square 3x3 that contain n  
    size_t x1 = (x/3)*3;
    size_t y1 = (y/3)*3;
    for(size_t i=0 ;i<3 ;i++){
        for(size_t j=0;j<3;j++){
            if (array[9*(y1+i)+(x1+j)]==n){
                return 0;
            }
        }
    }
    //the place is safe
    return 1;
}

//solver using backtraking algorithm 

void solve_pointers (int *array ,size_t len, int *array_res)
{
    //check for empty position in the  grid 
    for(size_t y=0 ;y<len;y++)
    {
        for(size_t x=0 ;x<len ;x++)
        {
            if (array[y*9 + x] ==0)
             {
                //testing
                for(size_t n=1 ;n<len+1;n++)
                {
                    if (safe_pointers(y,x,n,array,len))// n is safe at this position 
                    {
                        array[y*9+x]=n;
                        //backtaracking:
                        solve_pointers(array,len,array_res);//recursive call to fill  the next empty spaces
                        //#backtrack:n is not a solution(after the return)
                        array[y*9+x]= 0 ; // re replace the value by 0 after the return witch mean that the solution is incorrect 
                    }
                }
                return;//dead end ( if we try all the possible numbers from 1 to n at a specific coordinate ( x, y) and no one of them is correct 
            }

        }

    }
    //no more empty spaces : the end , solutuon is here !
    copy_arrays_pointers(array,array_res);

}



int main()
{
    int res[9][9];
    int res2[9][9];
    int *res_grid=&res[0][0];
    int *res2_grid=&res2[0][0];
    SDL_Surface *image = image_treatment("copie.jpeg");
    //SDL_Surface *image = image_treatment("image_01.jpg", 1, 0);
    SDL_Surface * array4[81];

    sudoku_detection(image, array4);
    init_sdl();
    SDL_Surface * w = display1(array4[9]);
    digit_recognition(array4,res_grid);
    //solve_pointers(res_grid , 9 , res2_grid);
    for (int i=0 ; i <81 ; i++)
    {
        printf("%i",res_grid[i]);
    }
    printf("\n");
    
}
