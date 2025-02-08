
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int hijo1,hijo2,hijo3;
int señal;
int contador;
int status;
int pid;



int main(){

    if(hijo1=fork()==0){
        sleep(9);
        exit(EXIT_SUCCESS);//0 y success es lo mismo
    }
    if(hijo2=fork()==0){
        sleep(6);
        exit(0);
    }
    if(hijo3=fork()==0){
        sleep(3);
        exit(0);
    }

    while(contador<3){//Que es mejor bucle o hacer wait por cada uno??
    contador++;
    pid=wait(&status);
    printf("Proceso hijo con pid %i ha finalizado\n",pid);
    printf("Salida con estado %i\n",WEXITSTATUS(status));//me devuelve el estado de salida del proceso hijo 0 success y 1 failure
    }


}