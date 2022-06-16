#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <openssl/md5.h>
#include <sys/wait.h>
#include "enc.h"
#include "shared_memory.h"
#include "read_write.h"


#define CHAN_PROGRAM "/chan"
#define MAX_TRIES 10


int main (int argc, char** argv)
{
    int SM_id = atoi(argv[1]);
    int id = atoi(argv[2]);     //id tou proccess
    Entry SM_ptr;
    char delim[] = "+";
    int flag;
    int flag2=0;
    int counter = 0;    //gia lathos mhnumata

    char string1[100];
    char string3[100];
    char string4[100];
    char string5[100];
    if((SM_ptr = SM_attach(SM_id)) == NULL )
    {
        perror("Shared memory attach ");
        exit(-1);
    } 

    if(id ==1)          //enc1
    {
        flag = 0;
    }
    else if (id == 3)   //enc2
    {
        flag =1;
    }


    read_or_write(0,SM_ptr,id-1);   //ksipna me

    while (1)
    {
        if(flag)    //an eimaste ston elegxo tou mhnmatos
        {
  
            strcpy(string1,SM_ptr->array);
            char *ptr = strtok(string1,delim);
            ptr = strtok(NULL,delim);
            strcpy(string5, string1);

            md5_hex(string5,string3,1);
        
            if( (strcmp(ptr,string3)) == 0)
            {
                strcat(SM_ptr->array,"+");
                strcat(SM_ptr->array,string3);
            }
            else
            {
                ++counter;
                
                if(flag2== 0 && counter <10)
                {
                    printf("Error at string, trying to send again\n"); 
                    //read_or_write(1,SM_ptr,id);

                }
                else if(flag2==1 && counter < 10)
                {
                    printf("Error at string, trying to send again\n"); 
                    //read_or_write(2,SM_ptr,id-1); 
                }
                else
                {
                    printf("Sending message anyways\n");
                }
                
            }
          
            flag=0;   //allagh gia to else apo katw
        }
        else
        {
            md5_hex(SM_ptr->array,string4,0);
            flag=1;     //allagh gia to if apo panw
        }



        if(flag2 == 0) //gia metadosh mhnumatos apo aristera pros deksia
        {
            flag2=1;
            read_or_write(1,SM_ptr,id);

        }
        else           //gia metadosh mhnuatos apo deksia pros aristera
        { 
            flag2=0;
            read_or_write(2,SM_ptr,id-1);    
        }
             
    }
    
    return 0;
}

void md5_hex(char* str,char *md5,int flag)
{
    unsigned char md5_bin[16]; //128bits = 16 bytes
    if(flag == 0)
    {
        MD5(str, strlen(str),md5_bin);
        for (int  i = 0; i < 16; i++) //16 hex chars
        {
        sprintf(md5 +2*i,"%02x",md5_bin[i]);
        }
        strcat(str, "+");
        strcat(str,md5);
    }
    else
    {
        MD5(str, strlen(str),md5_bin);
        for (int  i = 0; i < 16; i++) //16 hex chars
        {
        sprintf(md5 +2*i,"%02x",md5_bin[i]);
        }
    }
    
   
    
}

