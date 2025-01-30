#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

typedef struct msgBuffer{
    long msg_type;
    char msg_text[100];
}msgBuffer;

void main(){
    key_t key = ftok("progfile", 65);

    int msqid = msgget(key, 0644);

    msgBuffer msgBuf1;

    if(msgrcv(msqid, &msgBuf1, sizeof(msgBuf1.msg_text), 10, IPC_NOWAIT | MSG_NOERROR) != -1){
        printf("Message read from sender : %s\n", msgBuf1.msg_text);
    }else{
        printf("Error receiving message of type 10\n");
    }

    msgBuffer msgBuf2;

    if(msgrcv(msqid, &msgBuf2, sizeof(msgBuf2.msg_text), 5, IPC_NOWAIT | MSG_NOERROR) != -1){
        printf("Message read from sender: %s", msgBuf2.msg_text);
    }else{
        printf("Error receiving message of type 5\n");
    }
}