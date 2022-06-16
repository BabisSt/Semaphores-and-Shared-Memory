#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <string.h>

#include "shared_memory.h"
#include "read_write.h"
#include "enc.h"

#define ENC_PROGRAM "./SRC/enc"

#define SEM_NAME "/semaphore_example"
#define ITERS 2

char* write_line(Entry SM_ptr);
char* read_line(Entry SM_ptr);

int main(int argc, char** argv)
{
    int SM_id = atoi(argv[1]);
    int read_write_flag = atoi(argv[2]);
    int id = atoi(argv[3]);
    printf("SM_Id = %d\n",SM_id);
    Entry SM_ptr;
    char* string;
    char* string1;


    if((SM_ptr = SM_attach(SM_id)) == NULL )
    {
        perror("Shared memory attach ");
        exit(-1);
    }                                                                                  


    while (1)
    {
        if(read_write_flag == 1) //write        P1
        {   
 
            while(strcmp((string1 = write_line(SM_ptr)),"TERM") != 0)  //an diabasei TERM stamata  
            {     
                free(string1);                                      
                read_or_write(1,SM_ptr,id);                 
                read_line(SM_ptr); 
                
            }
            free(string1);  
            if(sem_post(&SM_ptr->left_mutex[id]) < 0)                 
            {
                perror("Sem post failed on child");
            }
            break;

        }
        else if(read_write_flag == 0) // read   P2
        {
            
            read_or_write(0,SM_ptr,id-1);
            while (strcmp( (string = read_line(SM_ptr)),"TERM") != 0)
            {
                free(string);
                write_line(SM_ptr);
                read_or_write(2,SM_ptr,id-1);
                
            }

            free(string);
            break;   
        }
        else
        {
            perror("Flag");
            exit(1);
        }
    
    }

return 0;  

}

    
char* write_line(Entry SM_ptr)
{
    printf("Write:  ");
    char line[50];
    scanf("%[^\n]%*c", line);
    char* string = strdup(line);
    strcpy(SM_ptr->array,line);
    fflush(stdin);
    fflush(stdout);

    return string;

}

char* read_line(Entry SM_ptr)
{
    char* string;

    char delim[] = "+";
    string = strdup(SM_ptr->array);
    char *ptr = strtok(string,delim);
    printf("Read:   %s\n",string);

    for (int j = 0; j < strlen(SM_ptr->array); j++)
    {

        SM_ptr->array[j] = 0;
    }
    return string;
}