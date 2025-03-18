#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct msg {
    long msgType;  // Tipo de mensaje (indicador de ingrediente)
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <número fumador>\n", argv[0]);
        exit(-1);
    }

    int fumador = atoi(argv[1]) - 1;  // Convertir 1-3 a índice 0-2
    char *nombresFumadores[] = {"Fumador 1 (Papel)", "Fumador 2 (Tabaco)", "Fumador 3 (Fósforos)"};
    int id[4];
    struct msg msg;

    // Conectar a las colas de mensajes
    for (int i = 0; i < 4; i++) {
        id[i] = msgget(7 + i, 0666);
        if (id[i] == -1) {
            perror("msgget");
            exit(-1);
        }
    }

    // Ingredientes que necesita este fumador
    int ingr1 = (fumador + 1) % 3;  // Primer ingrediente necesario
    int ingr2 = (fumador + 2) % 3;  // Segundo ingrediente necesario

    // Notificar al proveedor que el fumador está listo
    printf("[%s] -> Notificando al proveedor que estoy listo\n", nombresFumadores[fumador]);
    msg.msgType = 1;  // Establecer el tipo de mensaje
    printf("[%s] -> Enviando mensaje al proveedor con msgType = %ld\n", nombresFumadores[fumador], msg.msgType);
    msgsnd(id[3], &msg, sizeof(struct msg), 0);  // Notificar al proveedor

    while (1) {
        printf("[%s] -> Esperando ingredientes %s y %s\n", nombresFumadores[fumador],
               (ingr1 == 0) ? "Papel" : (ingr1 == 1) ? "Tabaco" : "Fósforos",
               (ingr2 == 0) ? "Papel" : (ingr2 == 1) ? "Tabaco" : "Fósforos");//para comprobar que ingredientes espera

        // Esperar a recibir el primer ingrediente
        msgrcv(id[ingr1], &msg, sizeof(struct msg), 1, 0);  // Recibir primer ingrediente
        printf("[%s] -> Recibido ingrediente %s\n", nombresFumadores[fumador],
               (ingr1 == 0) ? "Papel" : (ingr1 == 1) ? "Tabaco" : "Fósforos");

        // Verificar si el segundo ingrediente está disponible
        if (msgrcv(id[ingr2], &msg, sizeof(struct msg), 1, IPC_NOWAIT) != -1) {//no bloqueante si no hay mensaje que no se quede esperando
            printf("[%s] -> Recibido ingrediente %s\n", nombresFumadores[fumador],
                   (ingr2 == 0) ? "Papel" : (ingr2 == 1) ? "Tabaco" : "Fósforos");

            // Simular el tiempo de fumar
            printf("[%s] -> ¡Tengo ambos ingredientes! Fumando...\n", nombresFumadores[fumador]);
            sleep(5);
            printf("[%s] -> He terminado de fumar\n", nombresFumadores[fumador]);

            // Avisar al proveedor que ha terminado
            msg.msgType = 1;  // Tipo genérico para la confirmación
            msgsnd(id[3], &msg, sizeof(struct msg), 0);
            printf("[%s] -> Aviso al proveedor que he terminado\n", nombresFumadores[fumador]);
        } else {
            // Si el segundo ingrediente no está disponible, devolver el primer ingrediente a la cola
            printf("[%s] -> El segundo ingrediente no está disponible. Devolviendo el primer ingrediente.\n", nombresFumadores[fumador]);
            msgsnd(id[ingr1], &msg, sizeof(struct msg), 0);
        }
    }

    return 0;
}
