
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
        int respuesta=execl("./p2","p2","Hijo", "1",(char *)0);
        exit(EXIT_SUCCESS);//0 y success es lo mismo
    }
    if(hijo2=fork()==0){
        sleep(6);
        int respuesta=execl("./p2","p2","Hijo", "2",(char *)0);//lo primero es el path y despues los argumentos incluyendo nombre del programa
        exit(0);
    }
    if(hijo3=fork()==0){
        sleep(3);
        int respuesta=execl("./p2","p2","Hijo", "3",(char *)0);
        exit(0);
    }

    while(contador<3){
    contador++;
    pid=wait(&status);
    printf("Proceso hijo con pid %i ha finalizado\n",pid);
    printf("Salida con estado %i\n",WEXITSTATUS(status));//me devuelve el estado de salida del proceso hijo 0 success y 1 failure
    }


}