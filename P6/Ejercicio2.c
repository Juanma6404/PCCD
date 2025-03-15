#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char* argv[]){

    if (argc != 2){
        printf("Uso: %s <id>\n", argv[0]);
        exit(-1);
    }

    int id_cola = atoi(argv[1]);

    if( msgctl(id_cola, IPC_RMID, NULL) == -1){//en exito con la opcion rmid devuelve 0
        perror("msgctl");
    }//lo compruebo con ipcs -q

    }