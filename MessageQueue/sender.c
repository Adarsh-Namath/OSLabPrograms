#include<stdio.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>

typedef struct messageBuffer{
    long msg_type;
    char msg_text[100];
}messageBuffer;

void main(){
    key_t key = ftok("progfile", 65);

    int msgid = msgget(key, 0644 | IPC_CREAT);

    messageBuffer msgBuf1;
    msgBuf1.msg_type = 5;

    printf("Enter the first message to be sent: ");
    fgets(msgBuf1.msg_text, sizeof(msgBuf1.msg_text), stdin);

    if(msgsnd(msgid, &msgBuf1, sizeof(msgBuf1.msg_text),IPC_NOWAIT) != -1){
        printf("Message send from sender: %s\n", msgBuf1.msg_text);
    }else{
        printf("Error sending first message\n");
    }

    messageBuffer msgBuf2;
    msgBuf2.msg_type = 10;

    printf("Enter the second message to be sent: ");
    fgets(msgBuf2.msg_text, sizeof(msgBuf2.msg_text), stdin);

    if(msgsnd(msgid, &msgBuf2, sizeof(msgBuf2.msg_text), IPC_NOWAIT) != -1){
        printf("Message sent from sender: %s\n", msgBuf2.msg_text);
    }else{
        printf("Error sending second message\n");
    }
}