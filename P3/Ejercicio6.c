#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>


int ID_memoria1,ID_memoria2;
char *primer_address,*segundo_address;
int puerta1,puerta2,vuelta;
int puerta;



int main(int argc, char *argv[]){
    puerta=atoi(argv[1]);
    if(argc>3){
    ID_memoria1=atoi(argv[2]);
    ID_memoria2=atoi(argv[3]);
   

    }
    else{
        ID_memoria1 = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0666);
        ID_memoria2 = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0666);//DEVUELVE ID DE MEMORIA COMPARTIDA EN EXITO O -1 SI FALLO
        if (ID_memoria1 == -1 || ID_memoria2 == -1){
            perror("Error al crear memoria compartida");
            exit(-1);
        }
        printf("ID:%i\n",ID_memoria1);
        printf("ID:%i\n",ID_memoria2);
        

    }
    while(1){
        printf("Caminando por mi habitación\n");

        
        do{
        getchar();
        printf("Intentando acceder al pasillo de entrada a la Sección Crítica...\n");

        
        
        //printf("Intentando entrar en mi Sección Crítica...\n");
        primer_address = shmat(ID_memoria1, NULL, 0);//Asociamos el segmento de memoria asociado a esa id_memoria al espacio de direcciones del proceso
        segundo_address= shmat(ID_memoria2, NULL, 0);
            //Se asocia a la primera direccion disponible seleccionada por el sistema
            //Devuelve la direccion de inicio del segmento
            if(primer_address == (void *) -1) {
                perror("Error al asociar la zona de memoria compartida");
                exit(-1);
            }
        
        if((*primer_address==0) && (puerta==1)){
        
            printf("Dentro del pasillo\n");
            
            vuelta=0;
            
            continue;
            
        }
        else if((*segundo_address==0) && (puerta==2)){
            printf("Dentro del pasillo\n");
            

            vuelta=0;
           

            continue;
        }
        else{
            
            printf("Puerta Cerrada\n");
            vuelta=1;
        }}
        
        while(vuelta==1);
        getchar();
        printf("He accionado el pulsador\n");
        if(puerta==1){
            *segundo_address=1;
        }
        else if(puerta==2){
            *primer_address=1;
            
        }

        printf("Dentro de mi Sección Crítica\n");
        getchar();
        printf("He salido de mi Sección Crítica\n");
        if(puerta==1){
            *segundo_address=0;
        }
        else if(puerta==2){
            *primer_address=0;
        }
        
        shmdt(primer_address);
        shmdt(segundo_address);
        }


    }
