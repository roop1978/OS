#include <stdio.h>
#include <stdlib.h>

int main()
{
    // int RQ[100] = {82, 170, 43, 140, 24, 16, 190}; // Direct input
    int RQ[100], i, j, n = 7, TotalHeadMovement = 0, head, size, move, index, temp;

    // Commented out user input code lines
    printf("Enter the number of Requests\n");
    scanf("%d", &n);
    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++)
        scanf("%d", &RQ[i]);
    printf("Enter head position\n");
    scanf("%d", &head);
    printf("Enter total disk size\n");
    scanf("%d", &size);
    printf("Enter the head movement direction for high 1 and for low 0\n");
    scanf("%d", &move);

    /* logic for LOOK disk scheduling */
    /* logic to sort the request array */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (RQ[j] > RQ[j + 1])
            {
                temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    /* Find the first request greater than or equal to the head position */
    for (i = 0; i < n; i++)
    {
        if (head < RQ[i])
        {
            index = i;
            break;
        }
    }

    /* if movement is towards high value */
    if (move == 1)
    {
        // move rightwards from head to the highest request
        for (i = index; i < n; i++)
        {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }

        // move left to the smallest request
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }
    }

    /* if movement is towards low value (move == 0) */
    else
    {
        // move leftwards from the starting head position and service requests
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }
        // now move rightwards after servicing requests that were initially lower than starting head value
        for (i = index; i < n; i++)
        {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }
    }

    /* Print the total head movement */
    printf("Total head movement is %d\n", TotalHeadMovement);
    return 0;
}
