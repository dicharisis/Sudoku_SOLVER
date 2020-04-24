

#include "structs.h"



int push (posib_num data ,node ** top){

    node *temp=NULL;
    
    temp= (node*)malloc(sizeof(node));
    
    temp->next=*top;
    temp->data.value1=data.value1;
    temp->data.cell1=data.cell1;
    temp->data.value2=data.value2;
    temp->data.cell2=data.cell2;
  
   

    *top=temp;

    return 0;


}