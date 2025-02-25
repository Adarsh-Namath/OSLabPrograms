#include <stdio.h>
#include<stdlib.h>

typedef struct Process{
    int pid, at, bt, ct, tat, wt;
}Process;

void sortByArrivalTime(Process proc[], int n) {
    int min;
    for (int i = 0; i < n - 1; i++) {
        min = i;
        for (int j = i + 1; j < n ; j++) {
            if(proc[j].at < proc[min].at){
                min = j;
            }
        }
        Process temp = proc[i];
        proc[i] = proc[min];
        proc[min] = temp;
    }
}

void calculate(Process proc[], int n) {
    int currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        if (currentTime < proc[i].at) {
            currentTime = proc[i].at;
        }
        
        proc[i].ct = currentTime + proc[i].bt;
        currentTime = proc[i].ct;

        proc[i].tat = proc[i].ct - proc[i].at;

        proc[i].wt = proc[i].tat - proc[i].bt;
    }
}


void printProcessDetails(Process proc[], int n) {
    float totalWT = 0, totalTAT = 0;

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\t\tTurnaround Time\t\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        totalWT += proc[i].wt;
        totalTAT += proc[i].tat;
        printf("%d\t%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", proc[i].pid, proc[i].at, proc[i].bt, proc[i].ct, proc[i].tat, proc[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);
}

void main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *proc = malloc(n * sizeof(Process));

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &proc[i].at);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &proc[i].bt);
    }

    sortByArrivalTime(proc, n);

    calculate(proc, n);

    printProcessDetails(proc, n);
}
