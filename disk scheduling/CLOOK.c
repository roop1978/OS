#include <stdio.h>
#include <stdlib.h>

int main()
{
    //int  = {82, 170, 43, 140, 24, 16, 190}; // Direct input
    int RQ[100],i, j, n = 7, TotalHeadMovement = 0, head , size , move , index, temp;

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

    /* logic for C-LOOK disk scheduling */

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
        // move rightwards from head to the highest request servicing requests on the way
        for (i = index; i < n; i++)
        {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }

        // jump to the smallest request value and move left to service remaining requests
        TotalHeadMovement += abs(RQ[n - 1] - RQ[0]);
        head = RQ[0];

        // service the remaining requests
        for (i = 0; i < index; i++)
        {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }
    }

    /* if movement is towards low value */
    else
    {
        // move leftwards from head to the lowest request servicing requests on the way
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }

        // jump to the highest request and move right to left to service remaining requests
        TotalHeadMovement += abs(RQ[0] - RQ[n - 1]);
        head = RQ[n - 1];

        // service the remaining requests in right to left direction
        for (i = n - 2; i >= index; i--)
        {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }
    }
    /* Print the total head movement */
    printf("Total head movement is %d\n", TotalHeadMovement);
    return 0;
}
