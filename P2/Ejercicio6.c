
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int señal;
int contador;
int status1,status2,status3,status4,status5;
int pid1,res1,res2,res3,res4;



int main(){
    
    printf("Unai Simón ");

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
    res1=wait(&status1);
    res2=wait(&status2);
    res3=wait(&status3);
    
    if(res1==pid1||res2==pid1||res3==pid1){
        wait(&status4);
        printf("Rodri ");
        printf("Pedri ");
        printf("Lamine Yamal ");
        printf("Morata\n");
        return 0;
    }
 
    printf("Rodri ");
    wait(&status4);
    printf("Pedri ");
    printf("Lamine Yamal ");
    printf("Morata\n");
    return 0;
}




    
    



    






