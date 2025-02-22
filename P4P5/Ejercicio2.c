#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> //la del sleep
#include <string.h>

  struct argumento
    {
        int posicion;
        char cadena[64];
    };


void funcion_thread(void *arg){
    struct argumento *args = (struct argumento *)arg;
    printf("Posición: %d, Parámetro: %s\n", args->posicion, args->cadena);
    
      
}



int main(int argc, char *argv[]){
  
    pthread_t direccion[argc];

    for ( int i = 1; i < argc; i++)
    {
        struct argumento *argumento=malloc(sizeof(struct argumento));
        argumento->posicion = i;
        strcpy(argumento->cadena, argv[i]);        
        pthread_create(&direccion[i],NULL,(void *)funcion_thread,argumento);
    }
    pthread_exit(NULL); //CON RETURN NO PORQUE LE DA IGUAL SI TERMINAN EL RESTO DE HILOS CON ESTE NO ESTE NO TERMINA EL PROCESP
                        //DEJA SALIR DEL MAIN PERO MANTENIENDO LOS HILOS

}