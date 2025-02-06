#include <stdio.h>

int main() {
    int num_processes;
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);

    int arrival_times[num_processes];
    int burst_times[num_processes];
    int completion_times[num_processes];
    int waiting_times[num_processes];
    int turnaround_times[num_processes];

    // Get input for each process
    for (int i = 0; i < num_processes; i++) {
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &arrival_times[i]);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burst_times[i]);
    }
    // Sort the processes based on arrival time  bubble sort
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = 0; j < num_processes - i - 1; j++) {
            if (arrival_times[j] > arrival_times[j + 1]) {
                int temp = arrival_times[j];
                arrival_times[j] = arrival_times[j + 1];
                arrival_times[j + 1] = temp;
                temp = burst_times[j];
                burst_times[j] = burst_times[j + 1];
                burst_times[j + 1] = temp;
            }
        }
    }
    // Process the sorted processes
    int current_time = 0;
    int gantt_chart[100] = {0}; //getting completion time , waitingtime ,turnaround-time
    for (int i = 0; i < num_processes; i++) {
        if (arrival_times[i] <= current_time) {
            completion_times[i] = current_time + burst_times[i];
            waiting_times[i] = current_time - arrival_times[i];
            turnaround_times[i] = completion_times[i] - arrival_times[i];
            for (int j = 0; j < burst_times[i]; j++) {
                gantt_chart[current_time + j] = i + 1;
            }
            current_time += burst_times[i]; 
        } else {
            for (int j = 0; j < arrival_times[i] - current_time; j++) {
                gantt_chart[current_time + j] = -1;
            }
            completion_times[i] = arrival_times[i] + burst_times[i];
            waiting_times[i] = 0;
            turnaround_times[i] = burst_times[i];
            for (int j = 0; j < burst_times[i]; j++) {
                gantt_chart[arrival_times[i] + j] = i + 1;
            }
            current_time = completion_times[i];
        }
    }
    // Calculate the average waiting time and turnaround time
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < num_processes; i++) {
        avg_waiting_time += waiting_times[i];
        avg_turnaround_time += turnaround_times[i];
    }
    avg_waiting_time /= num_processes;
    avg_turnaround_time /= num_processes;
    // Calculate the total idle time
    int total_idle_time = 0;
    for (int i = 0; i < current_time; i++) {
        if (gantt_chart[i] == -1) {
            total_idle_time++;
        }
    }
    // Print the results
    printf("\nGantt Chart:\n");
    for (int i = 0; i < current_time; i++) {
        if (gantt_chart[i] == -1) {
            printf("| Idle ");
        } else {
            printf("| P%d ", gantt_chart[i]);
        }
    }
    printf("|\n");
    for (int i = 0; i <= current_time; i++) {
        printf("%d\t", i);
    }
    printf("\n\nProcess\tBurstTime\tArrivalTime\tCompletionTime\tWaiting Time\tTurnaroundTime\n");
    for (int i = 0; i < num_processes; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               i + 1, burst_times[i], arrival_times[i], completion_times[i], waiting_times[i], turnaround_times[i]);
    }
    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f", avg_turnaround_time);
    printf("\nTotal Idle Time: %d\n", total_idle_time);
    return 0;
}