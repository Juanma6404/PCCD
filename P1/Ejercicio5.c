#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#define T_PISO 10

int sigusr1,sigusr2;
int piso_maximo,piso_minimo,piso_actual;
int subidas,bajadas;
int cambio,num;
pid_t pid ;
//PREGUNTAR SIGSUSPEND Y SIGPENDING(GUARDA QUE BLOQUEO Y QUEDO PENDIENTE)
//PREGUNTAR LO DE HACER OTRAS TAREAS MIENTRAS SUBE BAJA
//PREGUNTAR EL RESTART
//PREGUNTAR LO DEL PRINTF VS WRITE
//VARIAS SEÑALES SEGUIDAS DE SUBIDA HACE COSAS RARAS
//SIGUE HACIENDO LA SUBIDA SI MANDO OTRAS SEÑALES



//FUNCION HANDLER DE LAS SEÑALES

void handler(int sig_term){

        if(sig_term == SIGQUIT){
    
            printf("Señal SIGQUIT capturada\n");
            printf("Numero de subidas: %i\n",subidas);
            printf("Numero de bajadas: %i\n",bajadas);

            
            exit(0);
            
        }

        else if(sig_term == SIGUSR1){ 
            if(piso_actual==piso_maximo){
                printf("No puede subir, esta en el piso mas alto\n\n");
                return;

            }
            printf("Atendiendo orden de subida\n");
            cambio=0;
            alarm(T_PISO);
            return;
        }
         else if(sig_term == SIGUSR2){
            if(piso_actual==piso_minimo){
                printf("No puede bajar, esta en el piso mas bajo\n\n");
                return;
            }
            printf("Atendiendo orden de bajada\n");
            cambio=1;
            alarm(T_PISO);
            return;
        }
        else if(sig_term == SIGALRM){
            if(cambio==0){
                piso_actual++;
                subidas++;
                pid_t pid = getpid();
                printf("El ascensor ha llegado al piso %i\n",piso_actual);
                printf("Ascensor %i esperando orden \n",pid);
                printf("Si quiere subir SIGUSR1,si quiere bajar SIGUSR2\n");

                return;
            }
            else if(cambio==1){
                piso_actual--;
                bajadas++;
                pid_t pid = getpid();
                printf("El ascensor ha llegado al piso %i\n",piso_actual);
                printf("Ascensor %i esperando orden \n",pid);
                printf("Si quiere subir SIGUSR1,si quiere bajar SIGUSR2\n");

                return;
            }
        }
}


int main(int argc, char* argv[]){

    struct sigaction sa; 
    int pausa;
    
     sa.sa_flags=SA_RESTART; //preguntar esto
    
    //Bucle para el manejo de las señales
    for (int signal = 1; signal < 65; signal++) {
       //if(signal==SIGUSR1 || signal==SIGUSR2 || signal==SIGQUIT){
            sa.sa_handler = handler;
            sigaction(signal, &sa, NULL);


      // }
        /*else{
            sa.sa_handler = SIG_IGN;//HANDLER POR DEFECTO PARA IGNORAR
            sigaction(signal, &sa, NULL);

        }*/
        
    }
    
    piso_maximo=atoi(argv[2]);
    piso_minimo=atoi(argv[1]);
    pid_t pid = getpid();
     //Obtener el pid del proceso
    printf("Ascensor %i esperando orden \n",pid);
    printf("Si quiere subir SIGUSR1,si quiere bajar SIGUSR2\n");

    do{
        pausa= pause();//Suspension hasta recibir señal
        while(cambio==1||cambio == 0){
            printf("PODRIA HACER COSAS AQUI METE UN NUMERO\n");
            scanf("%i",&num);
            printf("Metiste este numero %i\n",num);
        }
        
    }
    while (1);
    
    }