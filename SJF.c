#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct Process{
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
}Process;

void compute(Process proc[], int n){
    int currentTime = 0, completed = 0;

    printf("\nProcess Execution Order: ");
    while(completed < n){
        int idx = -1;
        int min_BT = INT_MAX;

        int i;
        for(i = 0; i < n; i++){
            if(proc[i].at <= currentTime && proc[i].rt > 0 && proc[i].bt < min_BT){
                min_BT = proc[i].bt;
                idx = i;
            }
        }

        if(idx == -1){
            int closestArrivalTime = INT_MAX;
            for(i = 0; i < n; i++){
                if(proc[i].rt > 0 && proc[i].at > currentTime && proc[i].at < closestArrivalTime){
                    closestArrivalTime = proc[i].at;
                }
            }
            currentTime = closestArrivalTime;
            continue;
        }

        proc[idx].rt = 0;
        currentTime += proc[idx].bt;
        proc[idx].ct = currentTime;

        printf("P%d->",proc[idx].pid);

        proc[idx].tat = proc[idx].ct - proc[idx].at;
        proc[idx].wt = proc[idx].tat - proc[idx].bt;
        
        completed++;
    }
}

void printProcessTable(Process proc[], int n){
    int i;
    float totalTAT = 0, totalWT = 0;

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT");
    for(i = 0; i < n; i++){
        totalTAT += proc[i].tat;
        totalWT += proc[i].wt;

        printf("\n%d\t%d\t%d\t%d\t%d\t%d", proc[i].pid, proc[i].at, proc[i].bt, proc[i].ct, proc[i].tat, proc[i].wt);
    }

    printf("\nAverage Turn Around Time: %.3f", totalTAT/n);
    printf("\nAverage Waiting Time: %.3f\n", totalWT/n);
}

int main(){
    int n, i;

    printf("Enter the no. of processes: ");
    scanf("%d", &n);

    Process *proc = malloc(n * sizeof(Process));

    printf("Enter the arrival time and burst time for each process: \n");
    for(i = 0; i < n; i++){
        proc[i].pid = i + 1;

        printf("Process %d AT, BT: ", i + 1);
        scanf("%d%d", &proc[i].at, &proc[i].bt);

        proc[i].rt = proc[i].bt;
    }
    
    compute(proc, n);
    printProcessTable(proc, n);

    free(proc);
    return 0;
}