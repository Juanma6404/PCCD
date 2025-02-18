#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>


int ID_memoria1,ID_memoria2;
char *primer_address,*segundo_address;

int puerta;



int main(int argc, char *argv[]){
    puerta=atoi(argv[1]);
    if(argc>3){
    ID_memoria1=atoi(argv[2]);
    ID_memoria2=atoi(argv[3]);
   

    }
    else{
        ID_memoria1 = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0666);//OWNER GROUP USER
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

        
        
        getchar();
        printf("Dentro del pasillo");
        getchar();

        //printf("Intentando acceder al pasillo de entrada a la Sección Crítica...\n");

        
        
        //printf("Intentando entrar en mi Sección Crítica...\n");
        primer_address = shmat(ID_memoria1, NULL, 0);//Asociamos el segmento de memoria asociado a esa id_memoria al espacio de direcciones del proceso
        segundo_address= shmat(ID_memoria2, NULL, 0);
            //Se asocia a la primera direccion disponible seleccionada por el sistema
            //Devuelve la direccion de inicio del segmento
            if(primer_address == (void *) -1) {
                perror("Error al asociar la zona de memoria compartida");
                exit(-1);
            }


        printf("He accionado el pulsador\n");
        if(puerta==1){
            *segundo_address=1;
        }
        else if(puerta==2){
            *primer_address=1;
            
        }
        
        getchar();
        printf("Intentando acceder a la Sección Crítica\n");

        if((*primer_address==0) && (puerta==1)){
        
            printf("Dentro de mi Sección Crítica\n");
            
            
            
            
            
        }
        else if((*segundo_address==0) && (puerta==2)){
        
            printf("Dentro de mi Sección Crítica\n");            

            
           

            
        }
        else if((*segundo_address==1) &&(puerta==2)){
            
            printf("Puerta cerrada. Saliendo del Pasillo...\n");
            getchar();
            *primer_address = 0;//es mi puerta de salida en terminos logicos igual que la de entrada del otro proceso
            printf("He accionado el pulsador\n\n");
            shmdt(segundo_address);
            printf("He salido del pasillo\n\n");
            continue;
        }

        else if((*primer_address==1) &&(puerta==1)){
            
            printf("Puerta cerrada. Saliendo del Pasillo...\n");
            getchar();
            *segundo_address = 0;//es mi puerta de salida en terminos logicos igual que la de entrada del otro proceso
            printf("He accionado el pulsador\n\n");
            shmdt(primer_address);
            printf("He salido del pasillo\n\n");
            continue;
        }
        
        
        getchar();
       

        
        printf("He salido de mi Sección Crítica\n");
        
        getchar();
        printf("He accionado el pulsador\n");
        if(puerta==1){
            *segundo_address=0;
        }
        else if(puerta==2){
            *primer_address=0;
        }
        
        shmdt(primer_address);
        shmdt(segundo_address);
        }
        
//NO EXCLUSION MUTUA PORQUE SON BOTONES CONMUTADORES Y SI UNO ESTA DENTRO EL OTRO NO

//INTERBLOQUEO SI PORQUE EL BOTON ESTA ANTES DE LA PUERTA Y PUEDEN CASI A LA VEZ DARLE Y SE QUEDAN LOS DOS FUERA


    }
