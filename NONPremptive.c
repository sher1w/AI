#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PROC 100

void bubbleSort(int n, int arr[], int br[], int pr[], int id[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1] ||
                (arr[j] == arr[j + 1] && pr[j] > pr[j + 1])) {

                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                temp = br[j];
                br[j] = br[j + 1];
                br[j + 1] = temp;

                temp = pr[j];
                pr[j] = pr[j + 1];
                pr[j + 1] = temp;

                temp = id[j];
                id[j] = id[j + 1];
                id[j + 1] = temp;
            }
        }
    }
}

void nonprep(int n, int arr[], int br[], int pr[], int id[]) {
    int wt[MAX_PROC], tt[MAX_PROC], ct[MAX_PROC];
    int curr_time = 0;
    bubbleSort(n, arr, br, pr, id);

    for (int i = 0; i < n; i++) {
        if (curr_time < arr[i]) {
            curr_time = arr[i];
        }
        wt[i] = curr_time - arr[i];
        tt[i] = wt[i] + br[i];
        ct[i] = curr_time + br[i];
        curr_time = ct[i];
    }

    int total_wt = 0, total_tt = 0;
    printf("\nProc\tArr-Time\tBurst\tPriority\tComp-Time\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tt += tt[i];
        printf("P%d\t%d\t\t%d\t%d\t\t%d\t\t%d\t\t%d\n", id[i], arr[i], br[i], pr[i], ct[i], tt[i], wt[i]);
    }
    printf("\nAvg Waiting Time: %.2f", (float)total_wt / n);
    printf("\tAvg Turnaround Time: %.2f", (float)total_tt / n);

    printf("\n\nGantt Chart:\n");

    curr_time = arr[0];
    printf("|");
    for (int i = 0; i < n; i++) {
        if (arr[i] > curr_time) {
            printf(" Idle |");
            curr_time = arr[i];
        }
        printf("\tP%d |", id[i]);
        curr_time += br[i];
    }
    printf("\n");
    int start_t = arr[0];
    printf("%d", start_t);
    int curr_t = start_t;
    for (int i = 0; i < n; i++) {
        if (arr[i] > curr_t) {
            printf(" \t%d", arr[i]);
            curr_t = arr[i];
        }
        curr_t += br[i];
        printf("   \t%d", curr_t);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arr[MAX_PROC], br[MAX_PROC], pr[MAX_PROC], id[MAX_PROC];


    for (int i = 0; i < n; i++) {
         printf("Enter Arrival time ,  Burst time, and Priority of Process %d:\n",i+1);
        scanf("%d", &arr[i]);
        scanf("%d", &br[i]);
        scanf("%d", &pr[i]);
        id[i] = i + 1;
        printf("\n");
    }

    nonprep(n, arr, br, pr, id);
    return 0;
}

