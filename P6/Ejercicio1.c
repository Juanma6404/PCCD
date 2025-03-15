#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
    int id_cola;
    int clave=1;

    if ((id_cola =msgget(clave, IPC_CREAT | 0666)) == -1){//ME DEVUELVE LA ID DE LA COLA(NO NULO SIEMPRE A NO SER QUE SEA ERROR)//si no pongo permisos no me deja enviarlo el ejer3 despues
        perror("msgget");
        exit(-1);
    }
    printf("%i\n", id_cola);
}