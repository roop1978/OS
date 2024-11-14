#include <stdio.h>

int main()
{
    int n, m; // n = number of processes, m = number of resource types
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int available[m], work[m], totalres[m], max[n][m], allocation[n][m], need[n][m], safe[n];
    char finish[n];
    int i, j, totalloc, state, value = 0;

    // Step 1: Input total instances of each resource
    printf("Enter total instances of each resource (R1 R2 ... R%d): ", m);
    for (i = 0; i < m; i++)
    {
        scanf("%d", &totalres[i]);
    }

    // Step 2: Input the maximum resource requirements for each process
    printf("\nEnter the maximum resources required for each process:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("Enter maximum resources of R%d for process P%d: ", j , i);
            scanf("%d", &max[i][j]);
        }
    }

    // Step 3: Input the resources currently allocated to each process
    printf("\nEnter the resources currently allocated to each process:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("Enter resources of R%d allocated to process P%d: ", j + 1, i);
            scanf("%d", &allocation[i][j]);
        }
    }

    // Step 4: Calculate the need matrix (max - allocation) for each process
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Step 5: Initialize the finish array to 0 (indicating unfinished)
    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    // Step 6: Calculate the available resources
    for (i = 0; i < m; i++)
    {
        totalloc = 0;
        for (j = 0; j < n; j++)
        {
            totalloc += allocation[j][i];
        }
        available[i] = totalres[i] - totalloc;
        work[i] = available[i];
    }

    // Display the Allocated, Maximum, and Needed resources matrices
    printf("\nAllocated Resources:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("\nMaximum Resources:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    printf("\nNeeded Resources:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    printf("\nAvailable Resources: ");
    for (i = 0; i < m; i++)
    {
        printf("%d ", available[i]);
    }
    printf("\n");

    // Step 7: Find the safe sequence using Banker's algorithm
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if ((finish[i] == 0) && (need[i][j] <= work[j]))
            {
                state = 1; // Process can proceed
            }
            else
            {
                state = 0; // Process cannot proceed
                break;
            }
        }

        if (state == 1)
        {
            // If process is safe, add its allocation to work and mark as finished
            for (j = 0; j < m; j++)
            {
                work[j] += allocation[i][j];
            }
            finish[i] = 1; // Mark process as finished
            safe[value] = i; // Add process to safe sequence
            ++value;
        }

        if (i == n - 1)
        {
            if (value == n)
            {
                break; // All processes are safe
            }
            else
            {
                i = -1; // Reset loop to check unfinished processes again
            }
        }
    }

    // Step 8: Output the safe sequence
    printf("\nSafe Sequence: ");
    for (i = 0; i < n; i++)
    {
        printf("P%d ", safe[i]);
    }
    printf("\n");

    return 0;
}
