
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
        printf("Unai Simón ");
        
        return 0;
    }

    if(fork()==0){
        printf("Carvajal ");
        return 0;
    }
    if(fork()==0){
        printf("Pau Torres ");
        return 0;
    }
    if(fork()==0){
        printf("Cubarsí ");
        return 0;
    }
    printf("Cucurella ");
    if(fork()==0){
        printf("Dani Olmo ");
        printf("Nico Williams ");
        return 0;
    }
    wait(&status1);
    wait(&status2);
    wait(&status3);
    
   
    printf("Rodri ");
    wait(&status4);
    printf("Pedri ");
    printf("Lamine Yamal ");
   
    
    

    printf("Morata\n");
    return 0;
}




    
    



    






