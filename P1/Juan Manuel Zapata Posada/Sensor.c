#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int pid_ascen,piso_sensor,pid_sensor;




void handler(int sig_term){

        if(sig_term == SIGUSR1){//señal que se recibe desde sigalrm del ascensor que indica que ya llego al piso
            alarm(5);
            
            return;
            
        }
        if(sig_term == SIGALRM){
            printf("Usted se encuentra en el piso %i \n",piso_sensor);
            kill(pid_ascen,14);
            return;
            
        }
        
}

int main(int argc, char *argv[]){//Pasarle  piso sensor
   
    int pid = getpid();
    printf("Mi pid es %i\n",pid);
    printf("Dame el pid del ascensor\n");
    scanf("%i",&pid_ascen);

    piso_sensor=atoi(argv[1]);
    int señal;
    struct sigaction sa; 
    int pausa;
    
    sa.sa_flags=SA_RESTART;
    sa.sa_handler = handler;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGALRM, &sa,NULL);

    do{
        pause();
    }
    while(1);
        
}
    