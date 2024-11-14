// non preemptive Shortest Job First (SJF) Scheduling Algorithm
#include <stdio.h>

int main()
{
    int n, at[10], bt[10], wt[10], tat[10], ct[10], p[10];
    int sum = 0, i, j, temp;
    float totaltat = 0, totalwt = 0;

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
    }

    // Sort processes by Arrival Time, then by Burst Time if Arrival Time is the same
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (at[i] > at[j] || (at[i] == at[j] && bt[i] > bt[j]))
            {
                // Swap Arrival Time
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                // Swap Burst Time
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap Process IDs
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate Completion Time, Turnaround Time, and Waiting Time
    for (i = 0; i < n; i++)
    {
        if (sum < at[i])
        {
            // If CPU is idle, move time forward to arrival time of current process
            sum = at[i];
        }
        sum += bt[i];
        ct[i] = sum;            // Completion Time
        tat[i] = ct[i] - at[i]; // Turnaround Time
        wt[i] = tat[i] - bt[i]; // Waiting Time

        // Accumulate total Turnaround Time and Waiting Time
        totaltat += tat[i];
        totalwt += wt[i];
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
