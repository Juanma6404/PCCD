#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

char vector_bit [31];



//FUNCION HANDLER DE LAS SEÑALES

void handler(int sig_term){

        

        if(sig_term == SIGTERM){
            vector_bit[sig_term-1] = '1';//Ponemos a 1 la posicion equivalente al numero de la señal
            printf("Señal SIGTERM capturada\n");
            printf("%s\n",vector_bit);
            exit(0);
            
        }
        else{
            vector_bit[sig_term-1] = '1';
            printf("Otra señal capturada\n");
           

        }

    }


int main(void){

    struct sigaction sa; 
    int pausa;
    sa.sa_handler = handler;



    for (int cont= 0; cont < 31; cont++) { //Inicializamos el vector de bits a 0
        vector_bit[cont]='0';
    }


    //Bucle para el manejo de las señales
    for (int signal = 1; signal < 32; signal++) {
       
        //Creamos el handler para cada señal gracias al bucle
        sigaction(signal, &sa, NULL);
    }
    

    do{
    pid_t pid = getpid(); //Obtener el pid del proceso
    printf("Proceso %i esperando señal \n",pid);
    pausa= pause();//Suspension hasta recibir señal
    }
    while (1);
    
    }