#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>


int sigusr1,sigusr2;



//FUNCION HANDLER DE LAS SEÑALES

void handler(int sig_term){

        

        if(sig_term == SIGTERM){
    
            printf("Señal SIGTERM capturada\n");
            printf("Numero de SIGUSR1: %i\n",sigusr1);
            printf("Numero de SIGUSR2: %i\n",sigusr2);

            
            exit(0);
            
        }

        else if(sig_term == SIGUSR1){               //PORQUE LOS IF A SECAS NO VALDRIAN
            printf("Señal SIGUSR1 capturada\n");    //PREGUNTAR SI PRINTF D PROBLEMAS Y MEJOR WRITE
            //sleep(15); //es para el testeo del mask
            sigusr1++;
            return;
        }
         else if(sig_term == SIGUSR2){
            printf("Señal SIGUSR2 capturada\n");
            sigusr2++;
            return;
        }



    }


int main(void){

    struct sigaction sa; 
    int pausa;
     
    
    //sa.sa_flags=SA_RESETHAND; //FLAG RESETHAND DEJA USAR EL HANDLER UNA VEZ
    //sa.sa_flags=SA_RESTART;  PREGUNTARLE,en principio con funcionas con read y write si tienes este flag se reinician y no se fastidian

    sigset_t set;
    sigemptyset(&set); //PREGUNTAR
    sigaddset(&set, SIGTERM); //bloquea esta señal 
    sigprocmask(SIG_BLOCK,&set,NULL);

    //Bucle para el manejo de las señales
    for (int signal = 1; signal < 65; signal++) {
       if(signal==SIGUSR1 || signal==SIGUSR2 || signal==SIGTERM){
            sa.sa_handler = handler;
            sigaction(signal, &sa, NULL);


       }
        else{
            sa.sa_handler = SIG_IGN;//HANDLER POR DEFECTO PARA IGNORAR
            sigaction(signal, &sa, NULL);

        }
        
    }
    

    do{


      
    pid_t pid = getpid(); //Obtener el pid del proceso
    printf("Proceso %i esperando señal \n",pid);
    pausa= pause();//Suspension hasta recibir señal
    }
    while (1);
    
    }