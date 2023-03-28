#include <stdio.h>

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

//copy 2 arrays : external function used in solver
void copy_arrays(int array[9][9], int newarray[9][9]){
    for (size_t i = 0; i < 9; i++){
        for (size_t j = 0; j < 9; j++){
            newarray[i][j] = array[i][j];
        }
    }
}


//solver:

//check if the position is safe for  value n  with coordiante x and y in the grid
int safe(size_t y , size_t x , int n , int array[9][9],size_t len) 
{
    //testing if a row contain n 
    for(size_t i=0 ;i<len ; i++){
        if (array[y][i]==n){
            return 0;
        }
    }
    //testing if a column contain n 
    for(size_t j=0 ;j<len ; j++){
        if (array[j][x]==n){
            return 0;
        }
    }
    //testing inside the square 3x3 that contain n  
    size_t x1 = (x/3)*3;
    size_t y1 = (y/3)*3;
    for(size_t i=0 ;i<3 ;i++){
        for(size_t j=0;j<3;j++){
            if (array[y1+i][x1+j]==n){
                return 0;
            }
        }
    }
    //the place is safe
    return 1;
}

//solver using backtraking algorithm 

void solve (int array[9][9],size_t len,int array_res[9][9] )
{
    //check for empty position in the  grid 
    for(size_t y=0 ;y<len;y++)
    {
        for(size_t x=0 ;x<len ;x++)
        {
            if (array[y][x] ==0)
             {
                //testing
                for(size_t n=1 ;n<len+1;n++)
                {
                    if (safe(y,x,n,array,len))// n is safe at this position 
                    {
                        array[y][x]=n;
                        //backtaracking:
                        solve(array,len,array_res);//recursive call to fill  the next empty spaces
                        //#backtrack:n is not a solution(after the return)
                        array[y][x] = 0 ; // re replace the value by 0 after the return witch mean that the solution is incorrect 
                    }
                }
                return;//dead end ( if we try all the possible numbers from 1 to n at a specific coordinate ( x, y) and no one of them is correct 
            }

        }

    }
    //no more empty spaces : the end , solutuon is here !
    copy_arrays(array,array_res);

}