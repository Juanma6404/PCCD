
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>


int hijo1,hijo2,hijo3;
int señal;
int contador;


void handler(int signal){

}

int main(){

    if(hijo1=fork()==0){
        sleep(3);
        return 0;
    }
    if(hijo2=fork()==0){
        sleep(4);
        return 0;
    }
    if(hijo3=fork()==0){
        sleep(5);
        return 0;
    }
    struct sigaction sigAction;
    sigAction.sa_handler = handler; //manejador de señales
    sigemptyset(&sigAction.sa_mask);
    sigAction.sa_flags = 0;
    sigaction(17, &sigAction, NULL);//SIGCHLD

    

    while(1){
        if(contador==3){
        return 0;
        }
        pause();
        contador++;
        printf("Proceso hijo finalizado\n");

    }


}