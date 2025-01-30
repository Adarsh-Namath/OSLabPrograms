#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    int parentToChild[2];
    int childToParent[2];

    if(pipe(parentToChild) || pipe(childToParent)){
        printf("Pipe failed\n");
        return 0;
    }

    int pid = fork();

    if(pid < 0){
        printf("Fork failed");
        return 0;
    }else if(pid > 0){
        close(parentToChild[0]);
        close(childToParent[1]);

        int n, i;
        printf("Enter the limit: ");
        scanf("%d",&n);

        int *nums = malloc(n * sizeof(int));

        printf("Enter the no.s: ");
        for(i = 0; i < n; i++){
            scanf("%d",&nums[i]);
        }

        write(parentToChild[1], &n, sizeof(int));
        write(parentToChild[1], nums, n * sizeof(int));

        int sum;
        read(childToParent[0], &sum, sizeof(int));

        printf("Sum received from child process\t Sum : %d\n", sum);
        
        free(nums);
        close(parentToChild[1]);
        close(childToParent[0]);
    }else{
        close(parentToChild[1]);
        close(childToParent[0]);

        int n;
        read(parentToChild[0], &n, sizeof(int));

        int *arr = malloc(n * sizeof(int));
        read(parentToChild[0], arr, n * sizeof(int));

        int i, sum = 0;
        for(i = 0; i < n; i++){
            sum += arr[i];
        }

        write(childToParent[1], &sum, sizeof(int));

        free(arr);

        close(parentToChild[0]);
        close(childToParent[1]);
    }
}