#include<stdio.h>
#include <err.h>
#include <string.h>//strlen function  only used 
#include "txt_file_2_grid.h"
#include "display.h"
#include "solver.h"

//variables used in main 
int grid[9][9]; //initial grid 
char ch_grid[9][9];//grid used for conversion : from .txt to tab
int grid_res[9][9]; // the result grid
//main function
int main(int argc, char *argv[]){

    //open the txt file
    if (argc != 2) {
        errx(1, "error : you need to enter the grid  file name ");
    }
    FILE *fp = fopen(argv[1], "r"); // open the file 
    if (fp == NULL)
    {
        printf("Cannot open the file %s", argv[1]);
        return 1;
    }
    //if the arguments are correct:
    //initialise a char array with a  length of  82 bytes ( 9x9 +one for '\0')
    const unsigned MAX_LENGTH = 82;
    char result[MAX_LENGTH];
    //result is the string to store data
    //read each charecters from the file and add them to the string exept empty characters and new lines.
    char ch;
    size_t i=0;
    while ((ch = fgetc(fp)) != EOF){
        if(ch != '\n' && ch!=' ') {
            result[i]= ch;
            i++;
        }
    }
    //close the file
    fclose(fp);
    result[i] = '\0';//add the final character to the string 
   //solver
    convert_char_1d_to_2d(result,ch_grid,9);
    convert_2d_char_to_2d_int(ch_grid,grid);
    solve(grid,9,grid_res);

    //save the reult in a new file 
    size_t l = strlen(argv[1]);
    //7 is the length of .result
    char result1[l+8];
    char ll[]=".result";
    size_t k=0;
    for(size_t i =0; i<l; i++){
        
            result1[i]=argv[1][i];
        
    }
    for(size_t j =l; j<(l+8); j++){
        if(j==l+7){
            result1[j]= '\0';
        }
        else{
                result1[j]=ll[k];
        }
        k++;
    }
    
    FILE *fp1= fopen(result1,"w");
    for(size_t i=0;i<9;i++){
        for(size_t j=0;j<9;j++){
            if(j==2 || j==5 || j ==8){  
                fprintf(fp1,"%d ",grid_res[i][j]); 
            }
            else{
                fprintf(fp1,"%d",grid_res[i][j]); 
            }    
        }
        if(i==2 || i==5){
            fprintf(fp1,"\n");
        }
        fprintf(fp1,"\n");
    }
    fclose(fp1);

    display(grid,grid_res,9); 
    return 0;
 }