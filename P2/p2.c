#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    //printf("Estos son los parametros:\n");
    for(int i=1;i<argc;i++){
        printf("%s ",argv[i]);
    }
    return 0;
}