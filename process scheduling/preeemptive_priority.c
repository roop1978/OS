#include <stdio.h>

void preemptivePriority(int processes[], int n, int burstTime[], int arrivalTime[], int priority[])
{
    int remainingTime[10], waitingTime[10], turnaroundTime[10], completionTime[10];
    int completed = 0, currentTime = 0, maxPriorityIndex = -1;
    int isProcessAvailable = 0;

    // Initialize remaining times as burst times
    for (int i = 0; i < n; i++)
    {
        remainingTime[i] = burstTime[i];
    }

    while (completed < n)
    {
        maxPriorityIndex = -1;
        isProcessAvailable = 0;

        // Find the highest priority process among those that have arrived and are unfinished
        for (int i = 0; i < n; i++)
        {
            if (arrivalTime[i] <= currentTime && remainingTime[i] > 0)
            {
                isProcessAvailable = 1;
                if (maxPriorityIndex == -1 || priority[i] > priority[maxPriorityIndex])
                {
                    maxPriorityIndex = i;
                }
            }
        }

        // If a process is available to execute
        if (isProcessAvailable)
        {
            // Execute the process with the highest priority for 1 unit of time
            remainingTime[maxPriorityIndex]--;
            currentTime++;

            // If the process is completed
            if (remainingTime[maxPriorityIndex] == 0)
            {
                completed++;
                completionTime[maxPriorityIndex] = currentTime;
                turnaroundTime[maxPriorityIndex] = completionTime[maxPriorityIndex] - arrivalTime[maxPriorityIndex];
                waitingTime[maxPriorityIndex] = turnaroundTime[maxPriorityIndex] - burstTime[maxPriorityIndex];
            }
        }
        else
        {
            currentTime++;
        }
    }

    // Display results
    printf("Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrivalTime[i], burstTime[i], priority[i], completionTime[i], waitingTime[i], turnaroundTime[i]);
    }

    // Calculate and display average waiting and turnaround times
    float avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++)
    {
        avgWaitingTime += waitingTime[i];
        avgTurnaroundTime += turnaroundTime[i];
    }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processes[10], burstTime[10], arrivalTime[10], priority[10];

    printf("Enter the arrival times, burst times, and priorities of the processes:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &burstTime[i]);
        printf("Process %d - Priority: ", i + 1);
        scanf("%d", &priority[i]);
        processes[i] = i + 1;
    }

    preemptivePriority(processes, n, burstTime, arrivalTime, priority);

    return 0;
}
