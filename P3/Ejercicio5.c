#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>


int ID_memoria;
char *primer_address;
int turno,vuelta;



int main(int argc, char *argv[]){
    turno = atoi(argv[1]);

    if(argc>2){
    ID_memoria=atoi(argv[2]);
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

        
        do{
        getchar();
        
        printf("Intentando entrar en mi Sección Crítica...\n");
        primer_address = shmat(ID_memoria, NULL, 0);//Asociamos el segmento de memoria asociado a esa id_memoria al espacio de direcciones del proceso
            //Se asocia a la primera direccion disponible seleccionada por el sistema
            //Devuelve la direccion de inicio del segmento
            if(primer_address == (void *) -1) {
                perror("Error al asociar la zona de memoria compartida");
                exit(-1);
            }
        
        if(*primer_address==turno){
        
        printf("Dentro de mi Sección Crítica\n");
        vuelta=0;
        }
        else{
            
            printf("Puerta Cerrada\n");
            vuelta=1;
        }}
        while(vuelta==1);
        getchar();
        printf("He salido de mi Sección Crítica\n");
        getchar();
        printf("He accionado el pulsador\n");
        if(*primer_address==0){
            *primer_address=1;
        }
        else{
            *primer_address=0;
        }
        shmdt(primer_address);
        }


    }
