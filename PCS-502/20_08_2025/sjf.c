#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int id;
    int arrival_time;
    int burst_time;
    int left_time;
    int waiting_time;
    int turn_around_time;
    int completion_time;
    int is_completed;
} process;

void non_preemptive_sjf(process *p, int n) {
    int completed = 0, current_time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    printf("\n--- Execution Log (Non-Preemptive SJF) ---\n");
    while (completed < n) {
        int idx = -1;
        int min_bt = 1000000;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !p[i].is_completed) {
                if (p[i].burst_time < min_bt) {
                    min_bt = p[i].burst_time;
                    idx = i;
                } else if (p[i].burst_time == min_bt) {
                    if (p[i].arrival_time < p[idx].arrival_time)
                        idx = i;
                }
            }
        }

        if (idx != -1) {
            int start_time = current_time;
            int end_time = current_time + p[idx].burst_time;

            current_time = end_time;
            p[idx].completion_time = end_time;
            p[idx].turn_around_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turn_around_time - p[idx].burst_time;
            p[idx].left_time = 0;
            p[idx].is_completed = 1;
            completed++;

            total_waiting_time += p[idx].waiting_time;
            total_turnaround_time += p[idx].turn_around_time;

            printf("Time %d-%d (P%d): runs %dms\n", start_time, end_time, p[idx].id, p[idx].burst_time);
        } else {
            printf("Time %d-%d (Idle)\n", current_time, current_time + 1);
            current_time++;
        }
    }

    printf("\n--- Process Table ---\n");
    printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               p[i].id, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turn_around_time, p[i].waiting_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

void preemptive_sjf(process *p, int n) {
    int completed = 0, current_time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;

    // last segment tracker: -2 = none yet, -1 = idle, >=0 = index of running process
    int last = -2;
    int seg_start = 0;

    printf("\n--- Execution Log (Preemptive SJF / SRTF) ---\n");
    while (completed < n) {
        int idx = -1;
        int min_left = 1000000000; // big number

        // Pick process with shortest remaining time among arrived ones
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].left_time > 0) {
                if (p[i].left_time < min_left ||
                   (p[i].left_time == min_left && (idx == -1 || p[i].arrival_time < p[idx].arrival_time)) ||
                   (p[i].left_time == min_left && p[i].arrival_time == p[idx].arrival_time && p[i].id < p[idx].id)) {
                    min_left = p[i].left_time;
                    idx = i;
                }
            }
        }

        // If the selected "state" (process or idle) changes, flush the previous segment
        if (idx != last) {
            if (last >= 0 && current_time > seg_start) {
                // flush a running process segment
                printf("Time %d-%d (P%d): P%d runs for %dms (total time left: %dms)\n",
                       seg_start, current_time, p[last].id, p[last].id,
                       current_time - seg_start, p[last].left_time);
            } else if (last == -1 && current_time > seg_start) {
                // flush an idle segment
                printf("Time %d-%d (Idle): CPU is idle\n", seg_start, current_time);
            }
            seg_start = current_time;
            last = idx;
        }

        // Advance time by 1ms: either run chosen process for 1ms or stay idle for 1ms
        if (idx == -1) {
            current_time++;
        } else {
            p[idx].left_time--;
            current_time++;

            if (p[idx].left_time == 0) {
                p[idx].completion_time   = current_time;
                p[idx].turn_around_time  = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time      = p[idx].turn_around_time - p[idx].burst_time;
                total_waiting_time      += p[idx].waiting_time;
                total_turnaround_time   += p[idx].turn_around_time;
                completed++;
                // We don't flush here—segment flush will happen automatically when selection changes
            }
        }
    }

    // Flush the final open segment (last process or idle)
    if (last >= 0 && current_time > seg_start) {
        printf("Time %d-%d (P%d): P%d runs for %dms (total time left: %dms)\n",
               seg_start, current_time, p[last].id, p[last].id,
               current_time - seg_start, p[last].left_time);
    } else if (last == -1 && current_time > seg_start) {
        printf("Time %d-%d (Idle): CPU is idle\n", seg_start, current_time);
    }

    // Process table
    printf("\n--- Process Table ---\n");
    printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               p[i].id, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turn_around_time, p[i].waiting_time);
    }

    // Averages
    printf("\nAverage Waiting Time: %.2f ms\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f ms\n", total_turnaround_time / n);
}

int main() {
    int n, choice;
    printf("Satyam Singh Rawat(C) - 61\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    process *p = (process *)malloc(sizeof(process) * n);
    printf("Enter details of all processes:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter details of P%d ->\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst_time);
        p[i].left_time = p[i].burst_time;
        p[i].is_completed = 0;
    }

    printf("\nChoose Scheduling Type:\n");
    printf("1. Preemptive SJF (SRTF)\n");
    printf("2. Non-Preemptive SJF\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            preemptive_sjf(p, n);
            break;
        case 2:
            non_preemptive_sjf(p, n);
            break;
        default:
            printf("Invalid choice!\n");
    }

    free(p);
    return 0;
}
