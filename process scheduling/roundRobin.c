#include <stdio.h>

void roundRobin(int processes[], int n, int burstTime[], int arrivalTime[], int quantum)
{
    int remainingTime[10], waitingTime[10], turnaroundTime[10], completionTime[10];
    int currentTime = 0, completed = 0;

    // Initialize remaining times as burst times
    for (int i = 0; i < n; i++)
    {
        remainingTime[i] = burstTime[i];
    }

    // Process scheduling loop
    while (completed < n)
    {
        int allIdle = 1;

        for (int i = 0; i < n; i++)
        {
            if (remainingTime[i] > 0 && arrivalTime[i] <= currentTime)
            {
                allIdle = 0;

                if (remainingTime[i] > quantum)
                {
                    currentTime += quantum;
                    remainingTime[i] -= quantum;
                }
                else
                {
                    currentTime += remainingTime[i];
                    completionTime[i] = currentTime;                        // Completion time
                    turnaroundTime[i] = completionTime[i] - arrivalTime[i]; // Turnaround time
                    waitingTime[i] = turnaroundTime[i] - burstTime[i];      // Waiting time
                    remainingTime[i] = 0;
                    completed++;
                }
            }
        }

        if (allIdle)
        {
            currentTime++;
        }
    }

    // Display results
    printf("P\tAT\tBT\tCT\tWT\tT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i], arrivalTime[i], burstTime[i], completionTime[i], waitingTime[i], turnaroundTime[i]);
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
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processes[10], burstTime[10], arrivalTime[10];

    printf("Enter the arrival times and burst times of the processes:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &burstTime[i]);
        processes[i] = i + 1;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    roundRobin(processes, n, burstTime, arrivalTime, quantum);

    return 0;
}
