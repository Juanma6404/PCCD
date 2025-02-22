#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> //la del sleep

int num;
char caracter;

void funcion_thread(void *arg){
    while(1){
        scanf(" %c",&caracter);
        if (caracter == 'q'){
            exit(0);
        }
        if(caracter != ' '){
            num++;
        }
    }
    /*scanf(" %c",&caracter);
    if (caracter == 'q'){
        exit(0);
    }
   if(caracter != ' '){
       num++;
   }*/
   
}



int main(int argc, char *argv[]){
    pthread_t *restrict  direccion;//QUE HACE RESTRICT?
    pthread_create(direccion,NULL,(void *)funcion_thread,NULL);
    while (1){
        
        sleep(1);
        printf("NUMERO CARACTERES : %d\n",num);
    }
    
}

// Por que cuando imprimo los caracteres a veces no da impreso el numero de caracteres? y por que no se imprime el numero de caracteres en tiempo real?