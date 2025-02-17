#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>


int ID_memoria;
char *primer_address;
int number1;

int main(int argc, char *argv[]){

    number1=atoi(argv[1]);
    

   
    ID_memoria = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0666);//DEVUELVE ID DE MEMORIA COMPARTIDA EN EXITO O -1 SI FALLO
    if (ID_memoria == -1){
        perror("Error al crear memoria compartida");
        exit(-1);
    }

    while(1){

    getchar();

    primer_address = shmat(ID_memoria, NULL, 0);//Asociamos el segmento de memoria asociado a esa id_memoria al espacio de direcciones del proceso
    //Se asocia a la primera direccion disponible seleccionada por el sistema
    //Devuelve la direccion de inicio del segmento
    if(primer_address == (void *) -1) {
        perror("Error al asociar la zona de memoria compartida");
        exit(-1);
    }
    *primer_address=number1;
    getchar();
    printf("NUMERO : %d\n",*primer_address);
    printf("ID: %i\n",ID_memoria);
    getchar();
    shmdt(primer_address);

    }
}