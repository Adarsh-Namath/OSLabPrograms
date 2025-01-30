#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
void main(){
    int pipefd[2];

    if(pipe(pipefd) == -1){
        printf("Pipe failed\n");
        return;
    }

    int pid = fork();

    if(pid < 0){
        printf("Fork failed\n");
        return;
    }else if(pid > 0){
        close(pipefd[0]);

        int num;
        printf("Enter a number: ");
        scanf("%d", &num);

        write(pipefd[1], &num, sizeof(int));
        close(pipefd[1]);
    }else{
        close(pipefd[1]);

        int n;
        read(pipefd[0], &n, sizeof(int));
        close(pipefd[0]);

        if((n & 1) == 0){
            printf("EVEN\n");
        }else{
            printf("ODD\n");
        }
    }

}