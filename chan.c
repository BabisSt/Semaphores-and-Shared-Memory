#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <math.h>
#include <openssl/md5.h>
#include <string.h>
#include <time.h>


#include "shared_memory.h"
#include "enc.h"
#include "read_write.h"



int main(int argc,char** argv)
{
    srand(time(0));
    int SM_id = atoi(argv[1]);
    int id = atoi(argv[2]);
    float per ;
    int flag =0;
   
    Entry SM_ptr;
    char string1[100];
    char string_save[100];
    char number[100];
    char delim[] = "+";
    int i = 0;
    

    sscanf(argv[3],"%f",&per);
   
    if((SM_ptr = SM_attach(SM_id)) == NULL )        //SM attach
    {
        perror("Shared memory attach ");
        exit(-1);
    }
   
    read_or_write(0,SM_ptr,id-1);
    while (1)
    {
        

        if( SM_ptr->message_flag == 0)
        {
            strcpy(string1,SM_ptr->array);
            strcpy(string_save,SM_ptr->array);
        }
        else
        {
            strcpy(string1,string_save);
            SM_ptr->message_flag = 0;
        } 


        char *ptr = strtok(string1,delim);      

        
        ptr = strtok(NULL,delim);
        strcpy(number,ptr);
        
        
        while(string1 && i < strlen(string1))   //allaske to mhnuma
        {
            
            float random = (float)rand() / ((float)RAND_MAX);
            if(random > per && string1[i] != ' ')
            {
                string1[i] = 'x';
            }
        
            i++;
        }
        
        
        for (int j = 0; j < strlen(SM_ptr->array); j++)
        {
            
            SM_ptr->array[j]= 0;
        }

        strcat(SM_ptr->array,string1);
        strcat(SM_ptr->array,"+");
        strcat(SM_ptr->array,number);
        if(flag == 0)
        {   
            read_or_write(1,SM_ptr,id);
                if(SM_ptr->message_flag == 0)
                    flag =1;
                else
                    flag=0;         

        }
        else
        {
            read_or_write(2,SM_ptr,id-1);
            flag=0;
        }


    }

    

    


    return 0;
}