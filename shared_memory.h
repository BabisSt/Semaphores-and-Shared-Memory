#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

typedef struct SM_Data
{
    int message_flag;
    sem_t left_mutex[4];
    sem_t right_mutex[4];
    
    char array[512];
}SM_Data;

typedef SM_Data* Entry;

int SM_init(int entries_num);

SM_Data* SM_attach(int SM_id);

int SM_dettach(SM_Data* SM_pointer);

int SM_destroy(int SM_id);
