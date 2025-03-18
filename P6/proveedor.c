#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>

struct msg {
    long msgType;  // Tipo de mensaje
};

int main() {
    char *ingredientes[] = {"Papel", "Tabaco", "Fósforos"};
    int primerNumero, segundoNumero, id[4];
    struct msg msg;
    msg.msgType = 1;  // Establecer el tipo de mensaje

    // Inicializar la semilla de la función rand() con el tiempo actual
    srand(time(NULL));

    // Crear y limpiar las colas de mensajes
    for (int i = 0; i < 4; i++) {
        id[i] = msgget(7 + i, 0666 | IPC_CREAT);
        msgctl(id[i], IPC_RMID, NULL);  // Limpiar cualquier mensaje residual
        id[i] = msgget(7 + i, 0666 | IPC_CREAT);
        if (id[i] == -1) {
            perror("msgget");
            exit(-1);
        }
    }

    // Esperar a que los fumadores estén listos
    printf("[Proveedor] -> Esperando a que los fumadores estén listos...\n");
    for (int i = 0; i < 3; i++) {
        msgrcv(id[3], &msg, sizeof(struct msg), 1, 0);  // Esperar confirmación de los fumadores
    }
    printf("[Proveedor] -> Todos los fumadores están listos. Comenzando...\n");

    while (1) {
        // Seleccionar dos ingredientes aleatorios
        primerNumero = rand() % 3;
        do {
            segundoNumero = rand() % 3;
        } while (segundoNumero == primerNumero);

        printf("[Proveedor] -> Poniendo ingredientes: %s y %s\n", ingredientes[primerNumero], ingredientes[segundoNumero]);

        // Enviar los ingredientes a las colas correspondientes
        msg.msgType = 1;  // Tipo genérico para los ingredientes
        msgsnd(id[primerNumero], &msg, sizeof(struct msg), 0);  // Enviar primer ingrediente
        printf("[Proveedor] -> Ingrediente %s enviado a cola %d\n", ingredientes[primerNumero], primerNumero);

        msgsnd(id[segundoNumero], &msg, sizeof(struct msg), 0);  // Enviar segundo ingrediente
        printf("[Proveedor] -> Ingrediente %s enviado a cola %d\n", ingredientes[segundoNumero], segundoNumero);

        // Esperar confirmación de que un fumador ha terminado
        msgrcv(id[3], &msg, sizeof(struct msg), 1, 0);
        printf("[Proveedor] -> Recibida confirmación de un fumador\n");
    }
}
