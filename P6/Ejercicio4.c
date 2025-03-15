#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg{
    long msgType;
    char msgText[100];
};




int main(int argc, char* argv[]){
    struct msg msg;
    if (argc != 2){
        printf("Uso: %s <id>\n", argv[0]);
        exit(-1);
    }
    
    int msgid = atoi(argv[1]);

    if (msgrcv(msgid, &msg, 100, 0, 0) == -1){
        perror("msgrcv");
        exit(-1);
    }

    printf("Mensaje recibido: %s\n", msg.msgText);//una vez lo quita d la cola ya no esta

}