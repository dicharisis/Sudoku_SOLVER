#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sudoku_solver.h"

 

int main(void ){

    cell puzzle[9][9];
    
   
//    size_t stacksize;
//    pthread_attr_t a;
//    pthread_attr_getstacksize(&a, &stacksize);
//    printf("Current stack size = %zu\n", stacksize);
//    pthread_attr_setstacksize(&a, 100000000);
//    pthread_attr_getstacksize(&a, &stacksize);
//    printf("New stack size= %zu\n", stacksize);
      
    sudoku_init(puzzle);
       

    sudoku_check(puzzle);
        
      
    if (simple_solve_loop(puzzle)==0){
     
       
         expert_solver(puzzle); 
    }   
 

}
