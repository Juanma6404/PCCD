#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>



char *primer_address;

int main(int argc, char *argv[]){

   
    while(1){
    getchar();
    primer_address = shmat(atoi(argv[1]), NULL, 0);//Asociamos el segmento de memoria asociado a esa id_memoria al espacio de direcciones del proceso
    //Se asocia a la primera direccion disponible seleccionada por el sistema
    //Devuelve la direccion de inicio del segmento
    if(primer_address == (void *) -1) {
        perror("Error al asociar la zona de memoria compartida");
        exit(-1);
    }
    getchar();
    printf("ZONA : %d\n",*primer_address);
    getchar();
    shmdt(primer_address);
    }



}