#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem_permiso[20], sem_terminar[20], sem_leer;
sem_t sem_leer[20], sem_terminar[20], sem_escribir;
int lectores = 0;
int escritores = 0;
int max_lectores_concurr;


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




int main(int argc, char* argv[]){

    

    int max_lectores = atoi(argv[1]);
    max_lectores_concurr = atoi(argv[2]);
    int max_escritores = atoi(argv[3]);
    pthread_t threadIdLectores[max_lectores];
    pthread_t threadIdEscritores[max_escritores];
    sem_init(&sem_leer, 0, max_lectores_concurr);
    sem_init(&sem_escribir, 0, 1);
    

    if (max_lectores_concurr>=max_lectores){
        printf("El número de lectores concurrentes debe ser menor que el de lectores totales\n");
        exit(-1);
    }

    for (int i = 0; i < max_lectores; i++){
        int *arg = malloc(sizeof(int)); //para que no de warning
        *arg = i+1;
        pthread_create(&threadIdLectores[i], NULL, lector, arg);
        sem_init(&sem_permiso[i], 0, 0);
        sem_init(&sem_terminar[i], 0, 0);
    }

    for (int i = 0; i<max_escritores; i++){
        int *arg = malloc(sizeof(int)); //para que no de warning        
        *arg = i+1;
        pthread_create(&threadIdEscritores[i], NULL, escritor, arg);
        sem_init(&sem_permiso[i], 0, 0);
        sem_init(&sem_terminar[i], 0, 0);
    }

    while(1){
        
        sleep(1);
        char opcion;
        int lector;
        int escritor;
        printf("1. Intentar Leer\n");
        printf("2. Finalizar Leer\n");
        printf("3. Intentar Escribir\n");
        printf("4. Finalizar Escribir\n");
        printf("5. Salir\n");
        scanf(" %c", &opcion);
        switch(opcion){
            case '1':
                printf("Introduzca el número del lector (de 1 a %i)\n", max_lectores);
                scanf(" %i", &lector);
                sem_post(&sem_permiso[lector]);
                break;  
            case '2':
                printf("Introduzca el número del lector (de 1 a %i)\n", max_lectores);
                scanf(" %i", &lector);
                sem_post(&sem_terminar[lector]);
                break;
            case '3':
                printf("Introduzca el número del escritor (de 1 a %i)\n", max_escritores);
                scanf(" %i", &escritor);
                sem_post(&sem_permiso[escritor]);
                break;
            case '4':
                printf("Introduzca el número del escritor (de 1 a %i)\n", max_escritores);
                scanf(" %i", &escritor);
                sem_post(&sem_terminar[escritor]);
                break;
            case '5':
                exit(1);
            default:
                printf("Opción no válida\n");
        }
    }
}