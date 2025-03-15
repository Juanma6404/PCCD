#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

int main(int argc, char* argv[]){

    if (argc != 2){
        printf("Uso: %s <id>\n", argv[0]);
        exit(-1);
    }

    int msgid = atoi(argv[1]);



    struct mymsg{
        long mtype;      // Tipo de mensaje
        char mtext[100]; // Texto del mensaje
    };

    struct mymsg msg;
    msg.mtype = 1;                     // Tipo de mensaje
    strcpy(msg.mtext, "Hola, mundo!"); // Texto del mensaje

    if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1){
        perror("msgsnd");
        exit(1);
    }
}

/*if (argc != 2){
    printf("Uso: %s <id>\n", argv[0]);
    exit(-1);
}

    El programa espera que se pase un argumento en la línea de comandos al ejecutarlo, que corresponde al ID de la cola de mensajes (msgid).
    Si no se pasa el argumento, el programa imprime el mensaje de uso y termina.

Convierte el argumento a un entero:

int msgid = atoi(argv[1]);

    atoi(argv[1]) convierte el argumento de la línea de comandos (el ID de la cola de mensajes) en un número entero.
    Este ID es el que se usará para enviar el mensaje.

Definición de la estructura del mensaje:

struct mymsg{
    long mtype;      // Tipo de mensaje
    char mtext[100]; // Texto del mensaje
};

    Aquí se define la estructura mymsg, que representa el mensaje a enviar. Tiene dos campos:
        mtype: Un valor de tipo long que indica el tipo de mensaje (es útil cuando quieres manejar diferentes tipos de mensajes en la misma cola).
        mtext: Un arreglo de caracteres (cadena de texto) que contiene el contenido del mensaje. En este caso, hasta 100 caracteres.

Inicialización del mensaje:

struct mymsg msg;
msg.mtype = 1;                     // Tipo de mensaje
strcpy(msg.mtext, "Hola, mundo!"); // Texto del mensaje

    Se crea una variable msg de tipo mymsg.
    msg.mtype = 1; establece que el tipo de mensaje es 1 (es arbitrario y se puede modificar según las necesidades).
    strcpy(msg.mtext, "Hola, mundo!"); asigna el texto "Hola, mundo!" al campo mtext del mensaje.

Envío del mensaje:

if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1){
    perror("msgsnd");
    exit(1);
}

    msgsnd(msgid, &msg, sizeof(msg.mtext), 0) envía el mensaje a la cola de mensajes especificada por msgid. El mensaje tiene la siguiente estructura:
        msgid: ID de la cola de mensajes donde se enviará el mensaje.
        &msg: Apunta al mensaje que queremos enviar.
        sizeof(msg.mtext): Especifica el tamaño de los datos del mensaje. En este caso, solo se envía el texto (mtext), no el tipo (mtype).
        El último parámetro (0) es para las banderas de control. En este caso, no se utiliza ninguna bandera especial.
    Si msgsnd devuelve -1, significa que hubo un error al enviar el mensaje. Se usa perror("msgsnd") para imprimir un mensaje de error y luego el programa termina con exit(1).*/