#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5

struct msg {
    long msgType;
    int tenedor;
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <id del filósofo (1-5)>\n", argv[0]);
        exit(-1);
    }

    int filosofo = atoi(argv[1]);
    if (filosofo < 1 || filosofo > NUM_FILOSOFOS) {
        printf("El id del filósofo debe ser entre 1 y 5.\n");
        exit(-1);
    }

    // Arrays para los identificadores de las colas de mensajes de los tenedores
    int cola_tenedor[NUM_FILOSOFOS];

    // Obtener las colas de mensajes para los 5 tenedores
    for (int i = 1; i <= NUM_FILOSOFOS; i++) {
        cola_tenedor[i - 1] = msgget(i, 0600);
        if (cola_tenedor[i - 1] == -1) {
            perror("Error al obtener cola de mensajes");
            exit(-1);
        }
    }

    struct msg tenedor[NUM_FILOSOFOS];

    // Tenedor izquierdo y derecho
    int tenedor_i = filosofo;           // El tenedor izquierdo es el mismo número que el filósofo
    int tenedor_d = filosofo == NUM_FILOSOFOS ? 1 : filosofo + 1; // El tenedor derecho es el siguiente

    // El filósofo intenta coger el tenedor izquierdo
    printf("Filósofo %d intentando coger el tenedor %d...\n", filosofo, tenedor_i);
    if (msgrcv(cola_tenedor[tenedor_i - 1], &tenedor[filosofo - 1], sizeof(struct msg), tenedor_i, 0) == -1) {
        perror("Error al recibir mensaje para el tenedor izquierdo");
        exit(-1);
    }
    printf("Filósofo %d cogió el tenedor %d\n", filosofo, tenedor_i);

    // El filósofo intenta coger el tenedor derecho
    printf("Filósofo %d intentando coger el tenedor %d...\n", filosofo, tenedor_d);
    if (msgrcv(cola_tenedor[tenedor_d - 1], &tenedor[filosofo - 1], sizeof(struct msg), tenedor_d, 0) == -1) {
        perror("Error al recibir mensaje para el tenedor derecho");
        exit(-1);
    }
    printf("Filósofo %d cogió el tenedor %d\n\n", filosofo, tenedor_d);

    // El filósofo come
    printf("*********** Filósofo %d comiendo ***********\n", filosofo);
    sleep(5);

    // El filósofo devuelve los tenedores
    printf("Filósofo %d devolviendo los tenedores...\n", filosofo);

    // Devolver tenedor izquierdo
    tenedor[filosofo - 1].msgType = tenedor_i;
    tenedor[filosofo - 1].tenedor = tenedor_i;
    if (msgsnd(cola_tenedor[tenedor_i - 1], &tenedor[filosofo - 1], sizeof(struct msg), IPC_NOWAIT) == -1) {
        perror("Error al devolver el tenedor izquierdo");
        exit(-1);
    }
    printf("Filósofo %d devolvió el tenedor %d\n", filosofo, tenedor_i);

    // Devolver tenedor derecho
    tenedor[filosofo - 1].msgType = tenedor_d;
    tenedor[filosofo - 1].tenedor = tenedor_d;
    if (msgsnd(cola_tenedor[tenedor_d - 1], &tenedor[filosofo - 1], sizeof(struct msg), IPC_NOWAIT) == -1) {
        perror("Error al devolver el tenedor derecho");
        exit(-1);
    }
    printf("Filósofo %d devolvió el tenedor %d\n", filosofo, tenedor_d);

    return 0;
}
