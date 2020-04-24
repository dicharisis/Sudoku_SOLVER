#include <stdio.h>
#include <stdlib.h>

#include "sudoku_solver.h"

 

int main(void ){

    cell puzzle[9][9];
    
   

      
    sudoku_init(puzzle);
       

    sudoku_check(puzzle);
        
      
    if (simple_solve_loop(puzzle)==0){
     
       
         expert_solver(puzzle); 
    }   
 

}
