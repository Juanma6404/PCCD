#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *proceso2(void *threadArg){
    printf("Pau-Torres ");
}
void *proceso3(void *threadArg){
    printf("Carvajal ");
}
void *proceso4(void *threadArg){
    printf("Cucurella ");
}
void *proceso5(void *threadArg){
    printf("Dani-Olmo ");
    printf("Nico-Williams ");
}

int main(){

pthread_t threadId1, threadId2, threadId3, threadId4;

    printf("Unai Simon ");
    pthread_create(&threadId1, NULL, proceso2, NULL);
    pthread_create(&threadId2, NULL, proceso3, NULL);
    pthread_create(&threadId3, NULL, proceso4, NULL);
    printf("Cubarsí ");
    pthread_join(threadId3, NULL);
    printf("Rodri ");
    pthread_join(threadId1, NULL);
    pthread_join(threadId2, NULL);
    pthread_create(&threadId4, NULL, proceso5, NULL);
    printf("Pedri ");
    printf("Lamin Yamal ");
    pthread_join(threadId4, NULL);
    printf("Morata\n");

}