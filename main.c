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


#include "shared_memory.h"
#include "enc.h"
#include "read_write.h"

#define SEM_NAME "/semaphore_example"
#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define INITIAL_VALUE 1

#define CHILD_PROGRAM "./sem_child"
#define ENC_PROGRAM "./enc"
#define CHAN_PROGRAM "./chan"




int main(int argc, char** argv)
{
    Entry SM_ptr;
    int SM_id;
    pid_t pid;

   
    int sem_key;
    if((SM_id = SM_init(5)) < 0)                   //SM init
    {
       perror("Ftok error ");
       exit(-1); 
    }
    

    
    if((SM_ptr = SM_attach(SM_id)) == NULL )        //SM attach
    {
        perror("Shared memory attach ");
        exit(-1);
    }

   
   
    for (int i = 0; i < 4; i++)
    {
                    
        if( (sem_key = sem_init(&(SM_ptr->left_mutex[i]),1,0)) < 0)      //init SEM
        {
            fprintf(stderr,"Semaphore init error for");
            exit(-2);
        }
        if( (sem_key = sem_init(&(SM_ptr->right_mutex[i]),1,0))< 0)      //init SEM
        {
            fprintf(stderr,"Semaphore init error for");
            exit(-2);
        }
    
    }
    SM_ptr->message_flag = 0;
    char* string_id = convertnumtostring(SM_id);    //allagh tou SM_id se string
    pid_t pids[5];
    
    for (int i = 0; i < 4; i++)
    {
    
        
        pids[i] = fork();

        if(pids[i] < 0)
        {
            perror("Failed to fork");
            exit(EXIT_FAILURE);
        }
        else if(pids[i] == 0)
        {    
            
            char* id = convertnumtostring(i);
            if((i == 0) &&(execl(CHILD_PROGRAM, CHILD_PROGRAM, string_id,argv[1],id,NULL) < 0) )     
            {
                perror("Failed to exec");
                exit(EXIT_FAILURE);
            }
            if(((i==1) || (i==3)) &&(execl(ENC_PROGRAM, ENC_PROGRAM, string_id,id,NULL) < 0))     
            {
                perror("Failed to exec");
                exit(EXIT_FAILURE);
            }
            if((i == 2) &&(execl(CHAN_PROGRAM,CHAN_PROGRAM, string_id,id,argv[2],NULL) < 0) )     
            {
                perror("Failed to exec");
                exit(EXIT_FAILURE);
            }
        }
    }
    
    // to programma perimenei
    int n =1,status;
    while (n > 0)
    {
        pid = wait(&status);
        printf("Child with pid %ld exited with status 0x%x \n",(long)pid,status);        
        --n;
        exit(0);
    }


    
    return 0;

}

