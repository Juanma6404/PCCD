#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>


int ID_memoria;
char *primer_address;


int main(int argc, char *argv[]){

    if(argc>1){
    ID_memoria=atoi(argv[1]);
    }
    else{
        ID_memoria = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0666);//DEVUELVE ID DE MEMORIA COMPARTIDA EN EXITO O -1 SI FALLO
        if (ID_memoria == -1){
            perror("Error al crear memoria compartida");
            exit(-1);
        }
        printf("ID:%i\n",ID_memoria);
    }
    while(1){
        printf("Caminando por mi habitación\n");

        getchar();
        
        printf("Intentando entrar en mi Sección Crítica...\n");
        
        primer_address = shmat(ID_memoria, NULL, 0);//Asociamos el segmento de memoria asociado a esa id_memoria al espacio de direcciones del proceso
        //Se asocia a la primera direccion disponible seleccionada por el sistema
        //Devuelve la direccion de inicio del segmento
        if(primer_address == (void *) -1) {
            perror("Error al asociar la zona de memoria compartida");
            exit(-1);
        }
        printf("Dentro de mi Sección Crítica\n");
        getchar();
        shmdt(primer_address);
        printf("He salido de mi Sección Crítica\n");
        }


    }
