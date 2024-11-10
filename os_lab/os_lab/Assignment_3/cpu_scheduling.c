#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// Define a structure for processes
typedef struct {
    int pid;            // Process ID
    int arrival_time;   // Arrival time of process
    int burst_time;     // CPU burst time
    int remaining_time; // Remaining burst time for preemptive scheduling
    int completion_time;// Completion time of process
    int turn_around_time; // Turnaround time
    int waiting_time;   // Waiting time
} Process;

// Function to implement Shortest Job First (Preemptive) Scheduling
void sjf_preemptive(Process processes[], int n) {
    int completed = 0, current_time = 0;
    int min_burst_time = 0;
    int shortest = -1;

    // While there are processes to be completed
    while (completed != n) {
        min_burst_time = 9999;
        shortest = -1;

        // Find the process with the shortest remaining time that has arrived and not yet completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && processes[i].remaining_time < min_burst_time) {
                min_burst_time = processes[i].remaining_time;
                shortest = i;
            }
        }

        // If no process is ready, increment time
        if (shortest == -1) {
            current_time++;
            continue;
        }

        // Process the selected job
        processes[shortest].remaining_time--;
        current_time++;

        // If the process is completed
        if (processes[shortest].remaining_time == 0) {
            completed++;
            processes[shortest].completion_time = current_time;
            processes[shortest].turn_around_time = processes[shortest].completion_time - processes[shortest].arrival_time;
            processes[shortest].waiting_time = processes[shortest].turn_around_time - processes[shortest].burst_time;
        }
    }

    // Print results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turn_around_time, processes[i].waiting_time);
    }
}

// Function to implement Round Robin Scheduling
void round_robin(Process processes[], int n, int quantum) {
    int remaining_time[n];
    int completed = 0, current_time = 0;

    // Initialize remaining time for all processes
    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    // Track if all processes are completed
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    while (completed < n) {
        int done_in_this_round = 0;
        for (int i = 0; i < n; i++) {
            // Only consider processes that have arrived and are not completed
            if (processes[i].arrival_time <= current_time && remaining_time[i] > 0) {
                // Execute the process for time quantum or remaining time
                int exec_time = (remaining_time[i] <= quantum) ? remaining_time[i] : quantum;
                remaining_time[i] -= exec_time;
                current_time += exec_time;

                // If the process is completed
                if (remaining_time[i] == 0) {
                    processes[i].completion_time = current_time;
                    processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;
                    completed++;
                }

                done_in_this_round = 1;
            }
        }

        // If no process was executed in this round, increment current time
        if (!done_in_this_round) {
            current_time++;
        }
    }

    // Print final process details after all are completed
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turn_around_time, processes[i].waiting_time);
    }
}

// Main function
int main() {
    Process processes[MAX];
    int n, quantum, choice;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input the details for each process
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1; // Process ID starts from 1
        printf("Enter Arrival Time for Process %d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter Burst Time for Process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time; // Initialize remaining time for preemptive SJF
    }

    // Display the menu for the user to choose the scheduling algorithm
    printf("\nChoose the scheduling algorithm:\n");
    printf("1. Shortest Job First (Preemptive)\n");
    printf("2. Round Robin\n");
    scanf("%d", &choice);

    // Execute the chosen scheduling algorithm
    if (choice == 1) {
        sjf_preemptive(processes, n);
    } else if (choice == 2) {
        printf("Enter time quantum for Round Robin: ");
        scanf("%d", &quantum);
        round_robin(processes, n, quantum);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}

