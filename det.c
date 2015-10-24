#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int cal(int, int, int*);

#define G_DIM 4
int DET[G_DIM][G_DIM];

int main(int argc, char **argv){
  srand(time(NULL));
  for ( int i=0; i<G_DIM; i++ ){
    for ( int j=0; j<G_DIM; j++ ){
      DET[i][j] = rand() % 10; 
      printf("%3d,", DET[i][j]);
    }   
    printf("\n");
  }

  int sum = 0;
  int exclude_arr[G_DIM];
  memset(exclude_arr,-1, G_DIM*sizeof(int));
  for ( int i = 0; i < G_DIM; i++ ){
    exclude_arr[0] = i;
    sum += DET[0][i] * cal(0, i, exclude_arr);
  }
  printf("result = %d\n", sum);
}

int is_qualified_col(int row, int col, int * exclude_arr){
  for ( int i = 0; i < row; i++ ){
    if ( exclude_arr[i] == col ) return 0;
  }   
  return 1;
}

int cal(int row, int col, int *exclude_arr){
  int current_row = row + 1;
  int exclude_arr_cpy[G_DIM];
  if ( current_row >= G_DIM ) { 
    return 1;
  }

  memcpy(exclude_arr_cpy, exclude_arr, G_DIM*sizeof(int));

  int sum = 0;
  for ( int i = 0; i < G_DIM; i++ ){
    if ( is_qualified_col(current_row, i, exclude_arr_cpy) ){
      exclude_arr_cpy[current_row] = i;
      sum += DET[current_row][i] * cal(current_row, i, exclude_arr_cpy);
    }   
  }
  return sum;
}
