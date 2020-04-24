


typedef enum {false=0,true=1} bool;

typedef struct CELL_CO{

    int row;
    int column;

} cell_co;




typedef struct CELL {
    int actual_value;      
    //bool is_write;
    int flag[9];
    
} cell ;





typedef struct POSIB_NUM{
    int factor;
    int value1;
    int value2;
    cell_co cell1; 
    cell_co cell2;
} posib_num;




typedef struct NODE{
    posib_num data;
   struct NODE *next;
} node ;
