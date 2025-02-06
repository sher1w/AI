#include<stdio.h>

float average(int *matrix,int n)
{
    float avg = 0.0;
    for(int i=0;i<n;i++)
        avg += matrix[i];
    return avg/n;
}

void PreemptivePriority(int n, int burst[], int arrival[], int priority[])
{
    int rem_burst[n], WT[n], TAT[n],completion[n];
    int smallest, count = 0,totaltime=0;
    for(int i=0; i<n; i++)
    {
        rem_burst[i] = burst[i];
        totaltime+=burst[i];
    }
    int temp_process_no[totaltime];
    priority[n]=9999;
    for(int time=0; count != n; time++)
    {
        smallest = n;
        for(int i=0; i<n; i++)
        {
            if(arrival[i]<=time && priority[i]<priority[smallest] && rem_burst[i]>0)
                smallest = i;
        }
        rem_burst[smallest]--;
        temp_process_no[time] = smallest;
        if(rem_burst[smallest] == 0)
        {
            count++;
            completion[smallest] = time+1;
            TAT[smallest] = completion[smallest] - arrival[smallest];
            WT[smallest] = TAT[smallest] - burst[smallest];
        }
    }
    printf("\nProcess\tBurst Time\tArrivalTime\tPriority\tTurnaround Time\tWaitingTime\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i,burst[i],arrival[i],priority[i],TAT[i],WT[i]);
    }
    printf("\nAverage waiting time : %.2f\n",average(WT,n));
    printf("Average turn-around time : %.2f\n",average(TAT,n));
    printf("Gantt Chart:\n");
    printf("|");
    for(int i=0; i<n; i++)
    {
        printf("       P%d |",i);
    }
    printf("\n");
    int prev_time = 0;
    for(int i = 0; i < totaltime; i++)
    {
        if(i == 0 || temp_process_no[i] != temp_process_no[i-1])
        {
            printf("%d       ",prev_time);
            prev_time = i+1;
        }
    }
    printf("%d\n",prev_time);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    int burst[n], arrival[n],priority[n+1];

    for(int i=0;i<n;i++)
    {
        printf("Process %d\n",i+1);
        printf("Enter Burst Time: ");
        scanf("%d",&burst[i]);
        printf("Enter Arrival Time: ");
        scanf("%d",&arrival[i]);
        printf("Enter Priority Time: ");
        scanf("%d",&priority[i]);
    }
    PreemptivePriority(n,burst,arrival,priority);
    return 0;
}