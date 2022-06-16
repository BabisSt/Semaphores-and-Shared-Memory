#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "shared_memory.h"
#include "read_write.h"

void read_or_write(int flag,Entry SM_ptr,int id)
{
    if (flag == 0 )            
    {
        if(sem_wait(&SM_ptr->left_mutex[id]) < 0)                 
            {
                perror("Sem post failed on child");
            }
    }
    else if (flag == 1)                             //metakinhsh mhnumatos apo aristera pros deksia
    {
        if(sem_post(&SM_ptr->left_mutex[id]) < 0)                 
        {
            perror("Sem post failed on child");
        }
        if(sem_wait(&SM_ptr->right_mutex[id]) < 0)                
        {
            perror("Sem post failed on child");
        }  
    }
    else if (flag == 2)                         //metakinhsh mhnumatos apo deksia pros aristera
    {
        if(sem_post(&SM_ptr->right_mutex[id]) < 0)                 
        {
            perror("Sem post failed on child");
        }
        if(sem_wait(&SM_ptr->left_mutex[id]) < 0)                 
        {
            perror("Sem post failed on child");
        }
       
    }
    
}

char* convertnumtostring(int numbertoconvert)  //converts numbers to string
{
    int length = (int)(numbertoconvert ? log10(numbertoconvert) + 1 : 1);
    char* stringrecords = malloc((length + 1) * sizeof(char));
    sprintf(stringrecords, "%d", numbertoconvert);
  
    return stringrecords;
}