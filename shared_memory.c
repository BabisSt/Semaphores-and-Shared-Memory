#include "shared_memory.h"
#include <sys/ipc.h>

int SM_init( int entries_num)
{
  
    int sm_id = shmget(IPC_PRIVATE,entries_num*sizeof(SM_Data), IPC_CREAT | 0666);
    return sm_id;
}

SM_Data* SM_attach(int SM_id)
{
    return shmat(SM_id,0, 0);
}

int SM_dettach(SM_Data* SM_pointer)
{
    return shmdt(SM_pointer);
}

int SM_destroy(int SM_id)
{
    return shmctl(SM_id, IPC_RMID, 0);
}