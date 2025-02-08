
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int señal;
int contador;
int status1,status2,status3,status4,status5;



int main(){
    
    if(fork()==0){
    int respuesta=execl("./p2","p2","Unai Simon",(char *)0);

        
        return 0;
    }

    if(fork()==0){
    int respuesta=execl("./p2","p2","Carvajal",(char *)0);

        return 0;
    }
    if(fork()==0){
    int respuesta=execl("./p2","p2","Pau Torres",(char *)0);

        return 0;
    }
    if(fork()==0){
    int respuesta=execl("./p2","p2","Cubarsi",(char *)0);

        return 0;
    }
    printf("Cucurella ");
    if(fork()==0){
    int respuesta=execl("./p2","p2","Dani Olmo","Nico Williams",(char *)0);
       
    return 0;
    }
    wait(&status1);
    wait(&status2);
    wait(&status3);
 
    printf("Rodri ");
    printf("Pedri ");
    printf("Lamine Yamal ");
    wait(&status4);
   
    
    

    printf("Morata\n");
    return 0;
}




    
    



    






