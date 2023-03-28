#include<stdio.h>

void red () {
  printf("\033[1;31m");
}
void white()
{
    printf("\033[0;37m");
}


//display the final solved grid ( v1 : command line interface only )
//compare the initial and solution grids to print different colors 
//array: intial grid 
//array2: solved grid 
void display(int array[9][9] , int array2[9][9] ,size_t len ){
    for(size_t i=0;i<len;i++)
    {
        for(size_t j=0;j<len;j++)
        {
            if (j==2 || j==5 || j==8)
            {
                
                if(array[i][j] != array2[i][j]) 
                {
                    red();
                    printf("%i ",array2[i][j]);
                }
                else{
                    white();
                    printf("%i ",array2[i][j]);
                }

            }
            else{
                if(array[i][j] != array2[i][j]) {
                    red();
                    printf("%i",array2[i][j]); 
                }
                else{
                    white();
                    printf("%i",array2[i][j]);
                }

            }
        }
        if (i==2 || i==5)
            printf("\n");
        printf("\n");
    }
}