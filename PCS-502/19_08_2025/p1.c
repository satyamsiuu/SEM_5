#include <stdio.h>

typedef struct {
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
} Process;

typedef struct {
    int pid;   // 0 means idle
    int start;
    int end;
} GanttBlock;

void print_gantt_chart_same_arrival(Process p[], int n) {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        printf("  P%d  |", p[i].pid);
    }
    printf("\n%d", p[0].arrival);
    for (int i = 0; i < n; i++) {
        printf("     %d", p[i].completion);
    }
    printf("\n");
}


void print_gantt_chart(GanttBlock gantt[], int n) {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        if (gantt[i].pid == 0)
            printf(" Idle |");
        else
            printf("  P%d  |", gantt[i].pid);
    }
    printf("\n%d", gantt[0].start);
    for (int i = 0; i < n; i++) {
        printf("     %d", gantt[i].end);
    }
    printf("\n");
}

void calculate_times_same_arrival(Process p[], int n, int arrival_time) {
    int current_time = arrival_time;
    for (int i = 0; i < n; i++) {
        current_time += p[i].burst;
        p[i].completion = current_time;
        p[i].turnaround = p[i].completion - arrival_time;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }
}

void calculate_times_diff_arrival(Process p[], int n) {
    int current_time = 0;
    GanttBlock gantt[100];
    int gantt_index = 0;

    for (int i = 0; i < n; i++) {
        // If CPU idle before this process arrives
        if (current_time < p[i].arrival) {
            gantt[gantt_index].pid = 0;  // idle
            gantt[gantt_index].start = current_time;
            gantt[gantt_index].end = p[i].arrival;
            gantt_index++;
            current_time = p[i].arrival;
        }

        gantt[gantt_index].pid = p[i].pid;
        gantt[gantt_index].start = current_time;
        current_time += p[i].burst;
        gantt[gantt_index].end = current_time;
        gantt_index++;

        p[i].completion = current_time;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }

    print_gantt_chart(gantt, gantt_index);
}

void sort_by_arrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, choice;
    printf("Satyam Singh Rawat(C) - 61\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[n];

    printf("Choose case:\n1. All processes have same arrival time\n2. Different arrival times\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        int common_arrival;
        printf("Enter common arrival time for all processes: ");
        scanf("%d", &common_arrival);

        for (int i = 0; i < n; i++) {
            p[i].pid = i + 1;
            p[i].arrival = common_arrival;
            printf("Enter burst time for process P%d: ", i + 1);
            scanf("%d", &p[i].burst);
        }

        calculate_times_same_arrival(p, n, common_arrival);

        printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
        for (int i = 0; i < n; i++) {
            printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
        }
        print_gantt_chart_same_arrival(p, n);

    } else if (choice == 2) {
        for (int i = 0; i < n; i++) {
            p[i].pid = i + 1;
            printf("Enter arrival time for process P%d: ", i + 1);
            scanf("%d", &p[i].arrival);
            printf("Enter burst time for process P%d: ", i + 1);
            scanf("%d", &p[i].burst);
        }

        sort_by_arrival(p, n);

        calculate_times_diff_arrival(p, n);

        printf("\nProcess info in execution order:\n");
        printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
        for (int i = 0; i < n; i++) {
            printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
        }

    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
