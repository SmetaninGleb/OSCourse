#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

struct process
{
    int num, at, bt, ct, tat, wt, time_to_end;
    bool is_done;
};

int main() {
    int n_of_processes;
    printf("Please, enter the number of processes: ");
    scanf("%d", &n_of_processes);
    int quantum;
    printf("Please, enter the quantum: ");
    scanf("%d", &quantum);
    struct process processes[n_of_processes];
    printf("Please, enter the Arrival time and Burst time for the processes:\n");
    for (int i = 0; i < n_of_processes; i++) {
        int ar_time, bu_time;
        printf("Arrival time for the [%d] process: ", i+1);
        scanf("%d", &ar_time);
        printf("Burst time for the [%d] process: ", i+1);
        scanf("%d", &bu_time);
        processes[i].num = i+1;
        processes[i].at = ar_time;
        processes[i].bt = bu_time;
        processes[i].time_to_end = bu_time;
        processes[i].is_done = false;
    }

    int time = 0;
    int n_of_done = 0;
    for (int j = 0;; j++) {
        if (n_of_done == n_of_processes) break;
        int i = j % n_of_processes;
        int min_at_index = -1;
        int min_at = INT32_MAX;
        while (processes[i].is_done || processes[i].at > time) {
            if (processes[i].at < min_at && !processes[i].is_done) {
                min_at_index = i;
            }
            if (n_of_processes - i == 1) {
                i = 0;
            } else {
                i++;
            }
            if (i == j % n_of_processes) {
                time = min_at;
                i = min_at_index;
                break;
            }
        }
        j = i;
        if (processes[i].time_to_end <= quantum) {
            processes[i].is_done = true;
            n_of_done++;
            processes[i].ct = time + processes[i].time_to_end;
            processes[i].tat = processes[i].ct - processes[i].at;
            processes[i].wt = processes[i].ct - processes[i].bt - processes[i].at;
            time += processes[i].time_to_end;
            continue;
        }
        processes[i].time_to_end -= quantum;
        time += quantum;
    }

    printf("P#\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n_of_processes; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                processes[i].num, processes[i].at, processes[i].bt, processes[i].ct, processes[i].tat, processes[i].wt);
    }

    float avr_tat = 0;
    float avr_wt = 0;
    for (int i = 0; i < n_of_processes; i++) {
        avr_tat += 1.0 * processes[i].tat;
        avr_wt += 1.0 * processes[i].wt;
    }
    avr_tat /= 1.0 * n_of_processes;
    avr_wt /= 1.0 * n_of_processes;

    printf("Average Turnaround Time: %f\n", avr_tat);
    printf("Average WT: %f\n", avr_wt);

    return 0;
}