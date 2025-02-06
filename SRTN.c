#include <stdio.h>

typedef struct {
    int arrival_time;
    int burst_time;
    int remaining_time;
    int process_id;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void srtf_scheduling(Process processes[], int num_processes) {
    int time = 0;
    int completed_processes = 0;
    printf("Gantt Chart:\n");
    while (completed_processes < num_processes) {
        // Find the process with the shortest remaining time
        Process *shortest_process = NULL;
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                if (shortest_process == NULL || processes[i].remaining_time < shortest_process->remaining_time) {
                    shortest_process = &processes[i];
                } else if (processes[i].remaining_time == shortest_process->remaining_time && processes[i].arrival_time < shortest_process->arrival_time) {
                    shortest_process = &processes[i];
                }
            }
        }

        // If no process is available, increment time
        if (shortest_process == NULL) {
            time++;
            continue;
        }

        // Execute the process with the shortest remaining time
        printf("P%d | ", shortest_process->process_id);
        shortest_process->remaining_time--;
        time++;


        //printf("%d ",)
        // Check if the process is completed
        if (shortest_process->remaining_time == 0) {
            shortest_process->completion_time = time;
            shortest_process->turnaround_time = shortest_process->completion_time - shortest_process->arrival_time;
            shortest_process->waiting_time = shortest_process->turnaround_time - shortest_process->burst_time;
            completed_processes++;
        }
    }
    printf("\n");

    // Print completion time, turnaround time, and waiting time for each process
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < num_processes; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
}

int main() {
    int num_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    Process processes[num_processes];
    for (int i = 0; i < num_processes; i++) {
        processes[i].process_id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    srtf_scheduling(processes, num_processes);

    return 0;
}
