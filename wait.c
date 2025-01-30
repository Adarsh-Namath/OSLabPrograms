#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
void main(){
    int pid = fork();

    if(pid < 0){
        printf("Fork Failed\n");
        return;
    }else if(pid == 0){
        int i;
        for(i = 1; i <= 50; i++){
            printf("%d ", i);
        }
    }else{
        wait(NULL);
        int i;
        for(i = 51; i <= 100; i++){
            printf("%d ", i);
        }
    }
}