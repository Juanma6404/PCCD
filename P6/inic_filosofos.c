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

int main() {
    // Identificadores de las colas de tenedores
    int cola_tenedor[NUM_FILOSOFOS];

    // Crear las colas de mensajes para cada tenedor
    for (int i = 1; i <= NUM_FILOSOFOS; i++) {
        cola_tenedor[i - 1] = msgget(i, 0600 | IPC_CREAT);
        if (cola_tenedor[i - 1] == -1) {
            perror("Error al crear cola de mensajes");
            exit(-1);
        }
        printf("Cola de tenedor %d creada con ID %d\n", i, cola_tenedor[i - 1]);
    }

    struct msg tenedor[NUM_FILOSOFOS];

    // Inicializar las colas de tenedores con los valores
    for (int i = 1; i <= NUM_FILOSOFOS; i++) {
        tenedor[i - 1].msgType = i;
        tenedor[i - 1].tenedor = i;
        if (msgsnd(cola_tenedor[i - 1], &tenedor[i - 1], sizeof(struct msg), IPC_NOWAIT) == -1) {
            perror("Error al enviar tenedor");
            exit(-1);
        }
        printf("Tenedor %d colocado en su cola.\n", i);
    }

    return 0;
}
