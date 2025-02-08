
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int hijo1,hijo2,hijo3;
int señal;
int contador;
int status1,status2,status3;



int main(){

    if((hijo1=fork())==0){
        sleep(9);//PARA COMPROBAR PROCESOS ZOMBIES
        exit(EXIT_SUCCESS);//0 y success es lo mismo
    }
    if((hijo2=fork())==0){
        sleep(6);
        exit(0);
    }
    if((hijo3=fork())==0){
        sleep(3);
        exit(0);
    }

    waitpid(hijo1,&status1,0);//hay procesos zombie porque si termina otro antes no se gestiona hasta que este de aqui si
    printf("Proceso hijo con pid %i ha finalizado\n",hijo1);
    printf("Salida con estado %i\n",WEXITSTATUS(status1));
    
    waitpid(hijo2,&status2,0);
    printf("Proceso hijo con pid %i ha finalizado\n",hijo2);
    printf("Salida con estado %i\n",WEXITSTATUS(status2));

    waitpid(hijo3,&status3,0);
    printf("Proceso hijo con pid %i ha finalizado\n",hijo3);
    printf("Salida con estado %i\n",WEXITSTATUS(status3));
    

    return 0;


}