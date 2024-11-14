/// preemtive shortest job first scheduling algorithm

#include <stdio.h>
#include <limits.h>

int main()
{
    int n, at[10], bt[10], wt[10], tat[10], ct[10], p[10];
    int remBt[10]; // Remaining burst time array
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = -1, finish_time;
    float totaltat = 0, totalwt = 0;
    int i;

    printf("Enter the total number of processes: ");
    scanf("%d", &n);

    // Process IDs
    for (i = 0; i < n; i++)
        p[i] = i + 1;

    // Input Arrival Time and Burst Time
    printf("\nEnter the Arrival Time and Burst Time of each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("Process %d - Arrival Time: ", p[i]);
        scanf("%d", &at[i]);
        printf("Process %d - Burst Time: ", p[i]);
        scanf("%d", &bt[i]);
        remBt[i] = bt[i]; // Initialize remaining time to burst time
    }

    // Loop until all processes are complete
    while (complete != n)
    {
        // Find the process with the smallest remaining burst time that has arrived
        minm = INT_MAX;
        shortest = -1;
        for (i = 0; i < n; i++)
        {
            if ((at[i] <= t) && (remBt[i] < minm) && remBt[i] > 0)
            {
                minm = remBt[i];
                shortest = i;
            }
        }

        // If no process is ready, increment time
        if (shortest == -1)
        {
            t++;
            continue;
        }

        // Decrease remaining burst time of the selected process
        remBt[shortest]--;

        // If a process gets completely executed
        if (remBt[shortest] == 0)
        {
            complete++;
            finish_time = t + 1;
            ct[shortest] = finish_time;                  // Completion time
            tat[shortest] = ct[shortest] - at[shortest]; // Turnaround time
            wt[shortest] = tat[shortest] - bt[shortest]; // Waiting time
            totaltat += tat[shortest];
            totalwt += wt[shortest];
        }

        // Increment time
        t++;
    }

    // Display Results
    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    // Display Averages
    printf("\nAverage Turnaround Time: %.2f\n", totaltat / n);
    printf("Average Waiting Time: %.2f\n", totalwt / n);

    return 0;
}
