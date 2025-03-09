#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem_permiso[20], sem_terminar[20], sem_leer;

void *lector(void *threadArgs) {
    while(1) {
        int lector = *(int *)threadArgs;

        //ESPERA A PERMISO PARA LEER
        printf("[Lector %i] -> Esperando a intentar leer...\n", lector);
        sem_wait(&sem_permiso[lector]);

        // ESPERO A LEER
        printf("[Lector %i] -> Intentando leer...\n", lector);
        sem_wait(&sem_leer);

        //LEO
        printf("[Lector %i] -> Leyendo...\n", lector);
        
        // ESPERO A QUE TERMINE DE LEER
        sem_wait(&sem_terminar[lector]);
        printf("[Lector %i] -> Fin lectura\n", lector);

        //AVISO DE QUE TERMINE DE LEER
        sem_post(&sem_leer);
    }
}



int main(int argc, char* argv[]) {
    char opcion;
    
    

    int max = atoi(argv[1]); //NUM TOTAL DE LECTORES
    int max_concurr = atoi(argv[2]); // NUM TOTAL LECTORES CONCURRENTES
    pthread_t threadId[max]; 
    sem_init(&sem_leer, 0, max_concurr); // INICIALIZO SEMAFORO CON EL MAX NUMERO CONCURRENTES

    
    if (max_concurr >= max) {
        printf("El número de lectores concurrentes debe ser menor que el de lectores totales\n");
        exit(-1);
    }

    // INICIALIZO SEMAFOROS DE CADA LECTOR
    for (int i = 0; i < max; i++) {
        int *arg = malloc(sizeof(int)); 
        *arg = i + 1; //NUMERO DEL LECTOR
        pthread_create(&threadId[i], NULL, lector, arg); //CREO EL HILO PARA CADA LECTOR

        sem_init(&sem_permiso[i], 0, 0);
        sem_init(&sem_terminar[i], 0, 0); 
    }

  
    while(1) {
        sleep(0.5);
        int lector;
        printf("1 Intentar Leer\n");
        printf("2 Finalizar Leer\n");
        printf("3 Salir\n");
        scanf(" %c", &opcion); 

        switch(opcion) {
            case '1':
                printf("Introduzca el número del lector (de 1 a %i)\n", max);
                scanf(" %i", &lector); // NUMERO DE LECTOR QUE LE PASO A LA FUNCION
                sem_post(&sem_permiso[lector]); // AVISO DE QUE PUEDE LEER
                break;  
            case '2':
                printf("Introduzca el número del lector (de 1 a %i)\n", max);
                scanf(" %i", &lector); 
                sem_post(&sem_terminar[lector]); // AVISO DE QUE TERMINO DE LEER
                break;
            case '3':
                exit(1); 
            default:
                printf("Opción no válida\n");
        }
    }
}
