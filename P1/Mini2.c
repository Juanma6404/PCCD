#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(void){

    int señal;
    pid_t pid;



    printf("Dame el numero de la señal\n");
    scanf("%i",&señal);
    printf("Dame el pid\n");
    scanf("%i",&pid);

    kill(pid,señal);//Envio de la señal recibida por teclado al proceso tambien recibido por teclado
    printf("Señal %i enviada al proceso %i\n",señal,pid);


    return 0;
    
}
    