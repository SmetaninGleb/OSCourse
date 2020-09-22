#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

struct process
{
    int num, at, bt, ct, tat, wt;
    bool is_done;
};

void sort(struct process *arr, int n_of_elements) {
    for (int j = 0; j < n_of_elements; j++) {
        for (int i = 0; i < n_of_elements - 1; i++) {
            if (arr[i].at > arr[i+1].at || arr[i].at == arr[i+1].at && arr[i].bt > arr[i+1].bt) {
                struct process t = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = t;
            }
        }
    }
}

int main() {
    int n_of_processes;
    printf("Please, enter the number of processes: ");
    scanf("%d", &n_of_processes);
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
        processes[i].is_done = false;
    }

    sort(processes, n_of_processes);
    
    int time = 0;
    bool are_all_processes_done = false;
    while (!are_all_processes_done) {
        int min_bt_index = -1;
        int min_bt = INT32_MAX;
        for (int i = 0; i < n_of_processes; i++) {
            if (processes[i].at > time) {
                break;
            }
            if (!processes[i].is_done && processes[i].bt < min_bt) {
                min_bt_index = i;
                min_bt = processes[i].bt;
            }
        }
        if (min_bt_index == -1) {
            are_all_processes_done = true;
            for (int i = 0; i < n_of_processes; i++) {
                if (!processes[i].is_done) {
                    are_all_processes_done = false;
                    break;
                }
            }
            if (are_all_processes_done) {
                break;
            }
            for (int i = 0; i < n_of_processes; i++) {
                if (!processes[i].is_done) {
                    time = processes[i].at;
                    break;
                }
            }
        } else {
            processes[min_bt_index].is_done = true;
            processes[min_bt_index].ct = time + processes[min_bt_index].bt;
            processes[min_bt_index].tat = processes[min_bt_index].ct - processes[min_bt_index].at;
            processes[min_bt_index].wt = time - processes[min_bt_index].at;
            time += processes[min_bt_index].bt;
        }
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