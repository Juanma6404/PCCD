#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[]){//pasarle pid ascensor
    int pid=atoi(argv[1]);
    int señal;
    do{
        printf("Que orden desea enviar?\n");
        printf("1-Subida\n2-Bajada\n3-Salir\n");
        scanf("%i",&señal);
        if(señal==1){
            printf("Usted ha seleccionado subir\n");
            kill(pid,SIGUSR1);
            continue;

            

        }
        else if(señal==2){
            printf("Usted ha seleccionado bajar\n");
            kill(pid,SIGUSR2);
            continue;
            
        }
        else if(señal==3){
            printf("Usted ha seleccionado salir\n");
            kill(pid,SIGQUIT);
            continue;
            
            
        }
        
    }
    while(1);
    return 0;
    
}
    