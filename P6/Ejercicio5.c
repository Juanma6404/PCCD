#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct msg{
    long msgType;
    int tenedor;
};

int main(int argc, char* argv[]){
    int id;
    int tenedor_d;
    int tenedor_i;
    int filosofo;

    if (argc != 2){
        printf("Uso: %s <numero de filósifo(1-5)>\n",argv[0]);
        exit(-1);
    }

    id = msgget(5, 0600 | IPC_CREAT);
    if (id == -1){
        perror("msgget");
    }

    struct msg tenedor[6];
    
    tenedor_d=atoi(argv[1]);
    filosofo=atoi(argv[1]);
    tenedor_i = atoi(argv[1])-1;
    if (tenedor_i == 0){
        tenedor_i = 5;
    }

    printf("Filósofo %d intentando coger el tenedor %d...\n", filosofo, tenedor_i);
    msgrcv(id, &tenedor[filosofo], sizeof(struct msg), tenedor_i, 0);
    printf("El filósofo %d cogió el tenedor %d\n", filosofo, tenedor_i);

    printf("Filósofo %d intentando coger el tenedor %d...\n", filosofo, tenedor_d);
    msgrcv(id, &tenedor[filosofo], sizeof(struct msg), tenedor_d, 0);
    printf("El filósofo %d cogió el tenedor %d\n\n", filosofo, tenedor_d);


    printf("Filósofo %d comiendo \n\n", filosofo);
    sleep(5);

    printf("Filósofo %d devolviendo los tenedores\n", filosofo);

    tenedor[tenedor_d].msgType =tenedor_d;
    tenedor[tenedor_d].tenedor =tenedor_d;//PODRIA HACERLO CON UNA SOLA STRUCT LA  VERDAD
    tenedor[tenedor_i].msgType = tenedor_i;
    tenedor[tenedor_i].tenedor = tenedor_i;

    msgsnd(id, &tenedor[tenedor_d], sizeof(struct msg), IPC_NOWAIT);
    msgsnd(id, &tenedor[tenedor_i], sizeof(struct msg), IPC_NOWAIT);

}