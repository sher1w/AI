#include <stdio.h>
#include <limits.h>
#define MAX 10
int arrival_time[MAX], burst_time[MAX], completion_time[MAX], turnaround_time[MAX], waiting_time[MAX], n;
int completed[MAX], process_order[MAX];
char process_name[MAX][4];
int idle_start[MAX], idle_end[MAX], idle_count = 0;
void sort_waiting_time() {
    int i, j, temp;
    char temp_name[4];
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (waiting_time[i] > waiting_time[j]) {
                temp = waiting_time[i];
                waiting_time[i] = waiting_time[j];
                waiting_time[j] = temp;

                temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;
                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;
                        temp = completion_time[i];
                completion_time[i] = completion_time[j];
                completion_time[j] = temp;
                temp = turnaround_time[i];
                turnaround_time[i] = turnaround_time[j];
                turnaround_time[j] = temp;
                sprintf(temp_name, "%s", process_name[i]);
                sprintf(process_name[i], "%s", process_name[j]);
                sprintf(process_name[j], "%s", temp_name);
            }
        }
    }
}
void sort_arrival_time() {
    int i, j, temp;
    char temp_name[4];
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (arrival_time[i] > arrival_time[j]) {
                temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;
                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;
                sprintf(temp_name, "%s", process_name[i]);
                sprintf(process_name[i], "%s", process_name[j]);
                sprintf(process_name[j], "%s", temp_name);
            }
        }
    }
}
int find_next_process(int current_time) {
    int i;
    int min_burst_time = INT_MAX;
    int index = -1;
    for (i = 0; i < n; i++) {
        if (!completed[i] && arrival_time[i] <= current_time && burst_time[i] < min_burst_time) {
            min_burst_time = burst_time[i];
            index = i;
        }
    }
    return index;
}

void print() {
    int i;
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", process_name[i], arrival_time[i], burst_time[i], completion_time[i], turnaround_time[i], waiting_time[i]);
    }
}
int main() {
    int i, current_time = 0, completed_count = 0;
    float avg_turnaround_time = 0.0, avg_waiting_time = 0.0;
    printf("Enter the number of processes: \n");
    scanf("%d", &n);
    printf("Enter the values of arrival time:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arrival_time[i]);
    }
    printf("Enter the values of burst time:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &burst_time[i]);
        completed[i] = 0;
    }
    for (i = 0; i < n; i++) {
        sprintf(process_name[i], "P%d", i + 1);
    }
    sort_arrival_time();
    int process_index;
    while (completed_count < n) {
        process_index = find_next_process(current_time);
        if (process_index == -1) {
            current_time++;
        } else {
            if (current_time < arrival_time[process_index]) {
                idle_start[idle_count] = current_time;
                idle_end[idle_count] = arrival_time[process_index];
                idle_count++;
                current_time = arrival_time[process_index];
            }
            completion_time[process_index] = current_time + burst_time[process_index];
            turnaround_time[process_index] = completion_time[process_index] - arrival_time[process_index];
            waiting_time[process_index] = turnaround_time[process_index] - burst_time[process_index];
      current_time = completion_time[process_index];
            completed[process_index] = 1;
            completed_count++;
        }
    }
    for (i = 0; i < n; i++) {
        avg_turnaround_time += turnaround_time[i];
        avg_waiting_time += waiting_time[i];
    }
    avg_turnaround_time = avg_turnaround_time / n;
    avg_waiting_time = avg_waiting_time / n;
    sort_waiting_time();
    int c = 1;
    for (i = 0; i < n; i++) {
        process_order[c] = completion_time[i];
        c++;}
    for (i = 0; i < n; i++) {
       printf("%d ", process_order[i]);
    }
    printf("\nGantt Chart:\n");
    for (i = 0; i < 2 * completion_time[n - 1]; i++) {
        printf(" -");
    }
    printf("\n|");
    int count = 0;
    int x = 1;
    for (i = 1; i <= 2 * completion_time[n - 1]; i++) {
        if (i == 2 * process_order[x]) {
            printf(" |");
            x++;
        } else if (i == 2 * idle_end[count]) {
            printf(" |");
            count++;
        } else if (i == 2 * (process_order[x - 1] + process_order[x]) / 2) {
            printf("%s", process_name[x - 1]);
        } else {
            printf("  ");
        }
    }
    printf("\n");
    for (i = 0; i < 2 * completion_time[n - 1]; i++) {
        printf(" -");
    }
    printf("\n");
    count = 0;
    x = 1;
    for (i = 0; i <= 2 * completion_time[n - 1]; i++) {
        if (i == 0) {
            printf("%d ", arrival_time[0]);
        } else if (i == 2 * process_order[x]) {
            printf("%d ", process_order[x]);
            x++;
        } else if (i == 2 * idle_end[count]) {
            printf("%d ", idle_end[count]);
            count++;
        } else {
            printf("  ");
        }
    }
    printf("\n\n\n");
    print();
    printf("Average Turnaround Time = %f, Average Waiting Time = %f\n", avg_turnaround_time, avg_waiting_time);
    printf("\n\n\n");
    return 0;
}
