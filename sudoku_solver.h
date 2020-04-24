#include "stack_functions.h"
#include <string.h>


#define USER_INPUT 0
#define FILE_INPUT 1





int sudoku_init(cell a[9][9]);

int sudoku_check(cell s[9][9]);

int big_square_solver(cell pzl[9][9]);

int little_square_solver(cell pzl[9][9]);

int row_solver(cell pzl[9][9]);

int column_solver(cell pzl[9][9]);

int sudoku_solution_checker(cell pzl[9][9]);

int print_puzzle(cell pzl[9][9]);

int print_bits(cell pz[9][9]);

int reserve_row(cell pzl[9][9],int row ,int value);

int check_row(cell pzl[9][9],int row,int value);

int reserve_column(cell pzl[9][9],int column ,int value);

int check_column(cell pzl[9][9],int column,int value);

int reserve_square(cell pzl[9][9],int row,int column,int value);

int square_worker(cell pzl[9][9],int row,int column,int value);

int check_square(cell pzl[9][9],int row,int column,int value);

int simple_solve_loop( cell pzl[9][9] );

int expert_solver( cell pzl[9][9] );

void find_doubles_in_row( cell pzl[9][9],node **top);

void find_doubles_in_square(cell pzl[9][9], node **top);

int try_the_stack(cell pzl[9][9],node *ptr,int i,char str[16]);

int solve(cell pzl[9][9],node *ptr,int i,char str[16]);

void bin(int decimalnum,char str[16]);




//---------DEC TO BIN FUNCTION------------------------------
void bin(int decimalnum,char str[16]) {


 
 
   for(int i = 15; i >= 0; i--){
     
     if((decimalnum & (1 << i)) != 0){
       str[i]='1';
     }   
     else{
       str[i]='0';
     } 
     
   }
   


} 

//--------END OF DEC TO BIN FUNCTION---------------------------





//---------PRINT BITS PUZZLE FUNCTION------------------------------

int print_bits(cell pzl[9][9]){

printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i=0;i<9;i++){

        printf("\n");

        if( (i==3) ||(i==6) || (i==9) ){
           printf("----------------------------------------------------------------------------------------------------------------------------------------------\n"); 
        }

        for(int j=0;j<9;j++){
            printf(" |v:%d|",pzl[i][j].actual_value);
            for(int k=0;k<9;k++){
                printf("%d",pzl[i][j].flag[k]);
            }
        printf("|");
        }
    }
    printf(" ");
    printf(" ");

printf("----------------------------------------------------------------------------------------------------------------------------------------------\n");

   
}
//---------END OF PRINT BITS PUZZLE FUNCTION------------------------------





//---------PRINT PUZZLE FUNCTION------------------------------
int print_puzzle(cell pzl[9][9]){
   
    printf("  1    2    3    4    5    6    7    8    9\n"); 
    printf("  -------------------------------------------\n");
    
    for(int row=0;row<9;row++){
        
        for(int column=0;column<9;column++){
            
            printf(" |%d| ",pzl[row][column].actual_value);
                        
        }
     printf("\n");  
     printf("  -------------------------------------------\n");
    
    } 

}
//---------END OF PRINT PUZZLE FUNCTION------------------------------




//---------RESERVE ROW FUNCTION------------------------------
int reserve_row(cell pzl[9][9],int row,int value){
    
    for (int column=0;column<9;column++){
        pzl[row][column].flag[value-1]=1;
    }   
}
//---------RESERVE ROW FUNCTION------------------------------

//---------CHECK ROW FUNCTION------------------------------
int check_row(cell pzl[9][9],int row,int value){
    
    for (int column=0;column<9;column++){
        if (pzl[row][column].actual_value==value){
            return 1;
        }
    }   
    return 0;
}
//---------END OF CHECK ROW FUNCTION------------------------------







//---------RESERVE COLUMN FUNCTION------------------------------
int reserve_column(cell pzl[9][9],int column,int value){
    
    for (int row=0;row<9;row++){
        pzl[row][column].flag[value-1]=1;
    }    

}
//---------END OF RESERVE COLUMN FUNCTION------------------------------


//---------CHECK COLUMN FUNCTION------------------------------
int check_column(cell pzl[9][9],int column,int value){
    
    for (int row=0;row<9;row++){
       if (pzl[row][column].actual_value==value){
            return 1;
        }
    }    
   return 0;
}
//---------END OF CHECK COLUMN FUNCTION------------------------------
 
 





//---------RESERVE SQUARE FUNCTION------------------------------
int reserve_square(cell pzl[9][9],int row,int column,int value){
        
   int p=0;
   int t=0;
   
   if (row<3){p=0;}

   else if (row<6){p=3;}  

   else if (row<9){p=6;}   
     
   if (column<3){t=0;}

   else if (column<6){t=3;}  

   else if (column<9){t=6;}     

   square_worker(pzl,p,t,value);

}
//---------END OF RESERVE SQUARE FUNCTION------------------------------




//---------SQUARE WORKER FUNCTION------------------------------
int square_worker(cell pzl[9][9],int row,int column,int value){

    for (int i=row;i<row+3;i++){
        for(int j=column;j<column+3;j++){
            pzl[i][j].flag[value-1]=1;
        }
    }

}
//---------END OF SQUARE WORKER FUNCTION------------------------------



//---------CHECK SQUARE FUNCTION------------------------------
int check_square(cell pzl[9][9],int row,int column,int value){
        
   int p=0;
   int t=0;
   
   if (row<3){p=0;}

   else if (row<6){p=3;}  

   else if (row<9){p=6;}   
     
   if (column<3){t=0;}

   else if (column<6){t=3;}  

   else if (column<9){t=6;}     

    for (int i=p;i<p+3;i++){
        for(int j=t;j<t+3;j++){
            if( pzl[i][j].actual_value==value){
                return 1;
            }
        }
    }
    
    return 0;
  

}
//---------END OF CHECK SQUARE FUNCTION------------------------------












//---------FIND DOUBLES IN ROW FUNCTION------------------------------
void find_doubles_in_row(cell pzl[9][9], node **top){
    
    posib_num pn;

    int counter,counter2=0;

    for(int row=0;row<9;row++){
        
        for(int num=0;num<9;num++) {     
            counter=0; 

            for(int column=0;column<9;column++){

                if ( (pzl[row][column].flag[num]==0)){
                   
                   if (counter==0){
                       pn.value1=num;
                       pn.cell1.row=row;
                       pn.cell1.column=column;                     
                   }  
                    if (counter==1){
                       pn.value2=num;
                       pn.cell2.row=row;
                       pn.cell2.column=column;  
                   }  
                              
                    counter++;
                }              
                 
                if (counter>2) break;
            
            } 
            
            if (counter==2){
              push(pn,top);
             
              counter2++; 
            }
        
        
        
        
        } 
    }
    
    

}
//---------END OF FIND DOUBLES IN ROW FUNCTION------------------------------



//---------FIND DOUBLES IN SQUARE FUNCTION------------------------------
void find_doubles_in_square(cell pzl[9][9], node **top){
    
    posib_num pn;

    int counter,counter2=0;

    for(int row=0;row<9;row++){
        
        for(int column=0;column<9;column++) {     
            counter=0; 

            for(int num=0;num<9;num++){

                if ( (pzl[row][column].flag[num]==0)){
                   
                   if (counter==0){
                       pn.value1=num;
                       pn.cell1.row=row;
                       pn.cell1.column=column;                     
                   }  
                    if (counter==1){
                       pn.value2=num;
                       pn.cell2.row=row;
                       pn.cell2.column=column;  
                   }  
                              
                    counter++;
                }              
                 
                if (counter>2) break;
            
            } 
            
            if (counter==2){
              push(pn,top);
             
              counter2++; 
            }
        
        
        
        
        } 
    }
    
    

}
//---------END OF FIND DOUBLES IN SQUARE FUNCTION------------------------------



//--------------------TRY THE STACK FUNCTION----------------------------------

int try_the_stack(cell pzl[9][9],node *ptr,int i,char str[16]){
    
   node  *temp_ptr=ptr;
   
    int combinations=1,digits=0;
   
    cell pzl_temp[9][9];
 
    while(temp_ptr!=NULL){
      digits++;
      
      temp_ptr=temp_ptr->next;
    } 



    for(int j=0;j<digits;j++){
      combinations*=2;
    }
       
    memcpy(pzl_temp,pzl,(81*sizeof(cell)) );

 
    
    
    temp_ptr=ptr;

    if ( (solve(pzl_temp,temp_ptr,i,str) ==1) || (i>combinations-2) ){
        
        //*i=*i+1;
         return 1;
        //try_the_stack(pzl,ptr,i);
      
    }
    
    else{
        
        return 0;
    }
    
    
}


//--------------------END OF TRY THE STACK FUNCTION---------------------------



//--------------------SOLVE FUNCTION----------------------------------

int solve(cell pzl[9][9],node *ptr,int i,char str[16]){
   
    node * temp_ptr1=ptr; 
    node * temp_ptr2=ptr;   
    
    //char str[16];
    int j=0;

    bin(i,str);

   
   
     //printf("\n combination bin= %s \n",str);
    // printf("\n combination dec = %d \n",i);
  
    while (temp_ptr1!=NULL)
    {
        temp_ptr1->data.factor=str[j]-'0';
        //printf("\n [%d][%d] = %d or %d\n",temp_ptr1->data.cell1.row,temp_ptr1->data.cell1.column,temp_ptr1->data.value1,temp_ptr1->data.value2);
       
        j++;
        temp_ptr1=temp_ptr1->next;
    }

   
    
    while (temp_ptr2!=NULL)
    {
         
        if ( (temp_ptr2->data.factor==0) && (check_row(pzl,temp_ptr2->data.cell1.row,temp_ptr2->data.value1+1)==0) && (check_column(pzl,temp_ptr2->data.cell1.column,temp_ptr2->data.value1+1)==0) && (check_square(pzl,temp_ptr2->data.cell1.row,temp_ptr2->data.cell1.column,temp_ptr2->data.value1+1)==0) ){
            
            pzl[temp_ptr2->data.cell1.row][temp_ptr2->data.cell1.column].actual_value=temp_ptr2->data.value1+1;
          
            
            //printf("\n [%d][%d] = %d \n",temp_ptr2->data.cell1.row+1,temp_ptr2->data.cell1.column+1,temp_ptr2->data.value1+1);
            
            for(int k=0;k<9;k++){
                 pzl[temp_ptr2->data.cell1.row][temp_ptr2->data.cell1.column].flag[k]=1;
            }

        }
        else if( (temp_ptr2->data.factor==1) && (check_row(pzl,temp_ptr2->data.cell1.row,temp_ptr2->data.value2+1)==0) && (check_column(pzl,temp_ptr2->data.cell1.column,temp_ptr2->data.value2+1)==0) && (check_square(pzl,temp_ptr2->data.cell1.row,temp_ptr2->data.cell1.column,temp_ptr2->data.value2+1)==0)){
            
            pzl[temp_ptr2->data.cell1.row][temp_ptr2->data.cell1.column].actual_value=temp_ptr2->data.value2+1;
           
            //printf("\n [%d][%d] = %d \n",temp_ptr2->data.cell1.row+1,temp_ptr2->data.cell1.column+1,temp_ptr2->data.value2+1);
            
            for(int k=0;k<9;k++){
                pzl[temp_ptr2->data.cell1.row][temp_ptr2->data.cell1.column].flag[k]=1;
            }

        }
        
        temp_ptr2=temp_ptr2->next;
    }

  

     
  
         
       
        //  printf("\n");
        //  print_puzzle(pzl);
        //  printf("\n");
        //  print_bits(pzl);
         sudoku_check(pzl);

    if (simple_solve_loop(pzl)==0){
         
        //  printf("\n");
        //  print_puzzle(pzl);
        //  printf("\n");
        //  print_bits(pzl);
         
         
         return 0;
    }
    else {
       
         return 1;
    }
    
   
   
}



//--------------------END OF SOLVE FUNCTION---------------------------





//---------INIT PUZZLE FUNCTION------------------------------
int sudoku_init(cell pzl[9][9] ) {

    int  in_num=0,temp=0;
       
    #if FILE_INPUT==1
      
      FILE *fp=NULL;
      char buffer[255];
    
      fp=fopen("sudoku.txt","r");   
      fscanf(fp,"%s",buffer);
      fclose(fp);

    
    
    #elif USER_INPUT==1    
      
      char row_ext[3]="0";
      char column_ext[3]="0";
     
    #endif
   
            

    for(int row=0;row<9;row++){        
        
        #if USER_INPUT==1
            if (row==0) 
                { strcpy(row_ext,"st"); }
            else if (row==1)
                { strcpy(row_ext,"nd"); }
            else if(row==2) 
                { strcpy(row_ext,"rd"); }
            else 
                { strcpy(row_ext,"th"); }
        #endif

       for(int column=0;column<9;column++){
            
            #if USER_INPUT==1
                if (column==0) { strcpy(column_ext,"st"); }
                else if (column==1){ strcpy(column_ext,"nd"); }
                else if(column==2) { strcpy(column_ext,"rd"); }
                else { strcpy(column_ext,"th"); }
                
                printf("Enter %d%s row and %d%s item \n",row+1,row_ext,column+1,column_ext);
                scanf(" %d",&temp);
            #endif
            
            #if FILE_INPUT==1
            
                temp=buffer[in_num]-'0';
                
               
            #endif
            
            if (temp!=0){
                
                pzl[row][column].actual_value=temp;
               
                
                for(int i=0;i<9;i++){
                    pzl[row][column].flag[i]=1;
                }


              
            }
            
            else { 
            
                pzl[row][column].actual_value=0;
               
                 
                for(int i=0;i<9;i++){
                    pzl[row][column].flag[i]=0;
                }
               
             }             
            #if FILE_INPUT==1
                in_num++;
            #endif
            }
        
        }     

    
       }
      

 //---------END OF INIT PUZZLE FUNCTION------------------------------       
    

    

//---------CHECK PUZZLE FUNCTION------------------------------
int sudoku_check(cell pzl[9][9]){        
        
      
    for(int row=0;row<9;row++){          
        
        for(int column=0;column<9;column++){

            if(pzl[row][column].actual_value!=0){
                
                reserve_row(pzl,row,pzl[row][column].actual_value);
               
                reserve_column(pzl,column,pzl[row][column].actual_value);
                reserve_square(pzl,row,column,pzl[row][column].actual_value);
            
            }                
            
        }                       
            
    }     

} 
//---------END OF CHECK PUZZLE FUNCTION------------------------------




//---------FIRST SOLVER FUNCTION------------------------------
int big_square_solver(cell pzl[9][9]){
 
   
   int counter=0,counter2=0;  
   int temp_row=0,temp_column=0;
   
   cell *target=NULL;

    for(int max_row=3;max_row<=9;max_row+=3){
      
      for(int max_column=3;max_column<=9;max_column+=3){   
       

        for(int num=0;num<9;num++){         
            counter=0;
            target=NULL;
            
           
            
            for (int row=max_row-3; row<max_row; row++){                        

                for (int column=max_column-3; column<max_column; column++){                    
                                                                        
                    if (pzl[row][column].flag[num]==0 && pzl[row][column].actual_value==0){
                                              
                        
                            counter++;
                            temp_row=row;
                            temp_column=column;
                            target=&pzl[row][column];   
                        
                                                
                    }                                          
                    if(counter>1) break;               
            
                }
                if (counter>1) break; 
            }
            

            if ( counter==1 )  {                
                
                
                target->actual_value=num+1;
                
                
                for(int i=0;i<9;i++){
                    target->flag[i]=1;
                }
                
                reserve_row(pzl,temp_row,target->actual_value);
                reserve_column(pzl,temp_column,target->actual_value);
                
                

                counter2++;
                }
            }   
         
        }
    }
     
      return counter2;
      }    

//---------END OF FIRST SOLVER FUNCTION------------------------------




//---------SECOND SOLVER FUNCTION------------------------------
int little_square_solver(cell pzl[9][9]){

    int counter=0,counter2=0;
    int temp_row=0,temp_column=0,temp=0;
    cell *target=NULL;

    for(int row=0;row<9;row++){
        
        for(int column=0;column<9;column++){
    
            counter=0;
            target=NULL;
            
            for(int num=0;num<9;num++){
                                                                     
                if(pzl[row][column].flag[num]==0 && pzl[row][column].actual_value==0){
                  counter++;
                  temp=num;
                  temp_row=row;
                  temp_column=column;
                  target=&pzl[row][column];
                 } 
                 if (counter>1) break;
                
            }
            if (counter==1){
                
                target->actual_value=temp+1;
                
                for(int i=0;i<9;i++){
                    target->flag[i]=1;
                }
                reserve_row(pzl,temp_row,target->actual_value);             
                reserve_column(pzl,temp_column,target->actual_value); 
                reserve_square(pzl,temp_row,temp_column,target->actual_value);
                
                counter2++;                
            }            
                 
        }
                
    }
  
    return counter2;
}    
//---------END OF SECOND SOLVER FUNCTION------------------------------





//---------ROW SOLVER FUNCTION------------------------------
int row_solver(cell pzl[9][9]){

    int counter=0,counter2=0;
    int temp_row=0,temp_column=0;
    cell *target=NULL;

    for(int num=0;num<9;num++){
        
        for(int row=0; row<9;row++){
            counter=0;
            target=NULL;
            
            for(int column=0;column<9;column++){
              
                                                                    
                if(pzl[row][column].flag[num]==0 && pzl[row][column].actual_value==0){
                    counter++;   
                    temp_row=row;
                    temp_column=column;          
                    target=&pzl[row][column];
                    
                }
                
                if (counter>1) break;
            }

            if (counter==1){
                target->actual_value=num+1;
            
                
                for(int i=0; i<9;i++){
                    target->flag[i]=1;
                }
                
                reserve_column(pzl,temp_column,target->actual_value);
                reserve_square(pzl,temp_row,temp_column,target->actual_value); 
                
                counter2++;              

            }          

        } 

    }

    return counter2;
}
//---------END OF ROW SOLVER FUNCTION------------------------------



//---------COLUMN SOLVER FUNCTION------------------------------
int column_solver(cell pzl[9][9]){

    int counter=0,counter2=0;
    int temp_row=0,temp_column=0;
    cell *target=NULL;

    for(int num=0;num<9;num++){
        
        for(int column=0; column<9;column++){
            counter=0;
            target=NULL;
            
            for(int row=0;row<9;row++){
              
                                                                     
                if(pzl[row][column].flag[num]==0 && pzl[row][column].actual_value==0){
                    counter++;   
                    temp_row=row;
                    temp_column=column;                                     
                    target=&pzl[row][column];
                    
                }
                
                if (counter>1) break;
            }

            if (counter==1){
                target->actual_value=num+1;
                
                
                for(int i=0; i<9;i++){
                    target->flag[i]=1;
                }
                
                reserve_row(pzl,temp_row,target->actual_value);
                reserve_square(pzl,temp_row,temp_column,target->actual_value);
                
                counter2++;
               

            }          

        } 
      
    }
    
    return counter2;

}
//---------END OF COLUMN SOLVER FUNCTION------------------------------




//---------SOLUTION CHECKER FUNCTION----------------------------------
int sudoku_solution_checker(cell pzl[9][9]){
   


   for(int row=0;row<9;row++){
       for(int column=0;column<9;column++){
           
           if( (pzl[row][column].actual_value)==0){
              return 0;  //PUZZLE NOT SOLVED
           }
                  
       }
   } 
   
printf("****GONGRATULATIONS SUDOKU SOLVED********\n");
         printf("\n");
         print_puzzle(pzl);
         printf("\n");
         print_bits(pzl);
return 1; //PUZZLE SOLVED

}
//---------END OF SOLUTION CHECKER FUNCTION-------------------------------
  



//---------SOLVE LOOP FUNCTION-----------------------------------------

int simple_solve_loop( cell pzl[9][9] ){
    int a=0,b=0,c=0,d=0;

    while(sudoku_solution_checker(pzl)==0){
      
        a=big_square_solver(pzl);
        //printf("\n big square solver = %d \n",a);
        b=little_square_solver(pzl);
        //printf("\n little square solver = %d \n",b);
        c=row_solver(pzl);
        //printf("\n row solver = %d \n",c);
        d=column_solver(pzl);
        //printf("\n column square solver = %d \n",d);

        if( (a==0) && (b==0) && (c==0)  && (d==0) ){

            return 0; //PUZZLE NOT SOLVED
        }

    }
    
return 1; //PUZZLE  SOLVED

}

//---------END OF SOLVE LOOP FUNCTION-------------------------------
  




//---------EXPERT SOLVE FUNCTION-----------------------------------------


int expert_solver( cell pzl[9][9] ){
  
    node * top=NULL;
    int i=0;
    char str[16];

   // find_doubles_in_row(pzl,&top);
    find_doubles_in_square(pzl,&top);

   
    while(try_the_stack(pzl,top,i,str)!=1){
        
        i=i+1;
               
    }

    printf("\n Posiible combinations in expert solver \n ");
    
    while(top!=NULL){
     
      printf("\n [%d][%d]  = %d or %d \n",top->data.cell1.row+1,top->data.cell1.column+1,top->data.value1+1,top->data.value2+1);
      top=top->next;
    } 
    
    printf("\n combination bin= %s \n",str);
    printf("\n combination dec = %d \n",i);
           



    return 0;
}  





 

//---------EXPERT SOLVE FUNCTION-----------------------------------------

