#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>





int main(int argc, char *argv[]){

   
    shmctl(atoi(argv[1]),IPC_RMID,NULL);
    return 0;

}