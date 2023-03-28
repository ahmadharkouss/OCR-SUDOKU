#include <stdio.h>
// functions used to copy data from file.txt  to the grid 

//convert 1d Char array to 2d char array
void convert_char_1d_to_2d(char array[] ,  char array2[9][9], size_t len2 ) {
    size_t k = 0 ;
    size_t c=0 ;
    for(size_t i=0 ;i<len2 ;i++)
    {
        k=c;
        for(size_t j=0;j<len2;j++)
        {
            array2[i][j]=array[k];
            k++;
        }
        c=k;
    }   
}
//convert 2d char array to 2d int array
void convert_2d_char_to_2d_int(char array[9][9] ,  int array2[9][9] )
 {
    for(size_t i=0 ;i<9 ;i++){
        for(size_t j=0 ;j<9 ;j++){
            if(array[i][j]=='.'){
                array2[i][j]=0;
            }
            else{
                array2[i][j]= (array[i][j])-'0';
            }
        }
    }

}
