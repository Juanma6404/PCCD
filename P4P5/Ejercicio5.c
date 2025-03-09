#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem_permiso[20], sem_terminar[20], sem_escribir;

void *escritor( void *threadArgs){
    while(1){
        int escritor = *(int *)threadArgs;
        printf("[Escritor %i] -> Esperando a intentar escribir...\n", escritor);
        sem_wait(&sem_permiso[escritor]);
        printf("[Escritor %i] -> Intentando escibir...\n", escritor);
        sem_wait(&sem_escribir);
        printf("[Escritor %i] -> Escribiendo...\n", escritor);
        sem_wait(&sem_terminar[escritor]);
        printf("[Escritor %i] -> Fin escritura\n", escritor);
        sem_post(&sem_escribir);
    }
}

int main(int argc, char *argv[]){

    

    int Escritores = atoi(argv[1]);
    pthread_t threadId[Escritores];
    sem_init(&sem_escribir, 0, 1);//SOLO UNO PUEDE

    for (int i = 0; i<Escritores; i++){
        int *arg = malloc(sizeof(int));      
        *arg = i+1;
        pthread_create(&threadId[i], NULL, escritor, arg);
        sem_init(&sem_permiso[i], 0, 0);
        sem_init(&sem_terminar[i], 0, 0);
    }

    while(1){
        char opcion;
        int escritor;
        printf("1. Intentar Escribir\n");
        printf("2. Finalizar Escribir\n");
        printf("3. Salir\n");
        scanf(" %c", &opcion);
        switch (opcion){
            case '1':
                printf("Introduzca el número del escritor (de 1 a %i)\n", Escritores);
                scanf(" %i", &escritor);
                sem_post(&sem_permiso[escritor]);
                break;
            case '2':
                printf("Introduzca el número del escritor (de 1 a %i)\n", Escritores);
                scanf(" %i", &escritor);
                sem_post(&sem_terminar[escritor]);
                break;
            case '3':
                exit(1);
            default:
                printf("Opción no válida\n");
                break;
        }
    }
}