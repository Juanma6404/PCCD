#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){

    int pausa;
    pid_t pid = getpid(); //Obtener el pid del proceso


    printf("Proceso %i esperando señal \n",pid);

    pausa= pause();//Suspension hasta recibir señal

    return 0;
    
    
    
}