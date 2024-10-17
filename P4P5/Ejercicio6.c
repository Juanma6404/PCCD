#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem_permiso_l[20], sem_terminar_l[20], sem_leer;
sem_t sem_permiso_e[20], sem_terminar_e[20], sem_escribir;
sem_t sem_paso,sem_ocupado;
int contador_e=0;
int contador_l=0;
int lectores = 0;
int escritores = 0;
int max_lectores_concurr;


void *escritor( void *threadArgs){
    while(1){

        
        int escritor = *(int *)threadArgs;
        printf("[Escritor %i] -> Esperando a intentar escribir...\n", escritor);
        //printf("AQUI");----EL TECLADO NO SINCRONIZA
        sem_wait(&sem_permiso_e[escritor]);
        
        contador_e++;
        

        
        printf("[Escritor %i] -> Intentando escibir...\n", escritor);
        sem_wait(&sem_escribir);

        if(contador_l>0){//SI HAY LECTORES LEYENDO NO PUEDO ENTRAR AUNQUE TENGA PRIORIDAD
            printf("Hay lectores usando el papel\n");
            sem_wait(&sem_ocupado);
            
        }
        
        printf("[Escritor %i] -> Escribiendo...\n", escritor);
        sem_wait(&sem_terminar_e[escritor]);
        printf("[Escritor %i] -> Fin escritura\n", escritor);
        contador_e--;
        sem_post(&sem_escribir);
        
        
        if(contador_e==0 || contador_l>0){//AVISO QUE NO HAY MAS ESCRITORES Y HAY LECTORES LEYENDO
            //printf("AQUI");
            sem_post(&sem_paso);
        }
    }
}



void *lector(void *threadArgs) {
    while(1) {
        int lector = *(int *)threadArgs;
   
        //ESPERA A PERMISO PARA LEER
        printf("[Lector %i] -> Esperando a intentar leer...\n", lector);
        sem_wait(&sem_permiso_l[lector]);
        printf("[Lector %i] -> Intentando leer...\n", lector);
        
        // ESPERO A LEER POR SI YA HAY MUCHOS LEYENDO
        sem_wait(&sem_leer);
        if(contador_e>0 && contador_l==0){//SI HAY ESCRITORES TIENEN PRIORIDAD

            
        
            
            sem_wait(&sem_paso);//ESPERO A QUE NO HAYA ESCRITORES
            //printf("AQUI");
            

            

            

            //LEO
            printf("[Lector %i] -> Leyendo...\n", lector);
            contador_l++;
        
            // ESPERO A QUE TERMINE DE LEER
            sem_wait(&sem_terminar_l[lector]);
            printf("[Lector %i] -> Fin lectura\n", lector);

            //AVISO DE QUE TERMINE DE LEER
            contador_l--;
        
            sem_post(&sem_leer);

            if(contador_l==0 && contador_e>0){//SI YA NO HAY MAS LECTORES CONCURRENTES LEYENDO INDICO QUE PUEDE IR EL ESCRITOR

                sem_post(&sem_ocupado);

            }
            


        }
        else{
            
         

            

            

            //LEO
            printf("[Lector %i] -> Leyendo...\n", lector);
            contador_l++;
        
            // ESPERO A QUE TERMINE DE LEER
            sem_wait(&sem_terminar_l[lector]);
            printf("[Lector %i] -> Fin lectura\n", lector);

            //AVISO DE QUE TERMINE DE LEER
            sem_post(&sem_leer);
            contador_l--;
            if(contador_l==0 && contador_e>0){//SI YA NO HAY MAS LECTORES CONCURRENTES LEYENDO INDICO QUE PUEDE IR EL ESCRITOR Y  HAY ESCRITORES QUE QUIEREN ESCRIBIR DABA CONFLCITO SI IBA UN LECTOR TERMINABA Y DESPUES UN ESCRITOR

                sem_post(&sem_ocupado);

            }
        
        
            

        }
        
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
    sem_init(&sem_ocupado,0,0);
    sem_init(&sem_paso,0,0);
    

    if (max_lectores_concurr>=max_lectores){
        printf("El número de lectores concurrentes debe ser menor que el de lectores totales\n");
        exit(-1);
    }

    for (int i = 0; i < max_lectores; i++){
        int *arg = malloc(sizeof(int)); 
        *arg = i+1;
        pthread_create(&threadIdLectores[i], NULL, lector, arg);
        sem_init(&sem_permiso_l[i], 0, 0);
        sem_init(&sem_terminar_l[i], 0, 0);
    }

    for (int i = 0; i<max_escritores; i++){
        int *arg = malloc(sizeof(int)); //para que no de warning        
        *arg = i+1;
        pthread_create(&threadIdEscritores[i], NULL, escritor, arg);
        sem_init(&sem_permiso_e[i], 0, 0);
        sem_init(&sem_terminar_e[i], 0, 0);
    }

    while(1){
        
        sleep(1.5);
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
                sem_post(&sem_permiso_l[lector]);
                break;  
            case '2':
                printf("Introduzca el número del lector (de 1 a %i)\n", max_lectores);
                scanf(" %i", &lector);
                sem_post(&sem_terminar_l[lector]);
                break;
            case '3':
                printf("Introduzca el número del escritor (de 1 a %i)\n", max_escritores);
                scanf(" %i", &escritor);
                sem_post(&sem_permiso_e[escritor]);
                //printf("Dando permiso a escritor %d\n", escritor);

                break;
            case '4':
                printf("Introduzca el número del escritor (de 1 a %i)\n", max_escritores);
                scanf(" %i", &escritor);
                sem_post(&sem_terminar_e[escritor]);
                break;
            case '5':
                exit(1);
            default:
                printf("Opción no válida\n");
        }
    }
}