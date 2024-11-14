// <--------- C SCAN ------------->

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int RQ[100], i, j, n, TotalHeadMovement = 0, head, size, move, index, temp;
    printf("Enter the number of Requests\n");
    scanf("%d", &n);
    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++)
        scanf("%d", &RQ[i]);
    printf("Enter head head position\n");
    scanf("%d", &head);
    printf("Enter total disk size\n");
    scanf("%d", &size);
    printf("Enter the head movement direction for high 1 and for low 0\n");
    scanf("%d", &move);

    /* Sort the request array */
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

    /* Find the index where requests are greater than the head position */
    for (i = 0; i < n; i++)
    {
        if (head < RQ[i])
        {
            index = i;
            break;
        }
    }

    /* If movement is towards higher values */
    if (move == 1)
    {
        // Service requests from the starting head position to the last request in the array
        for (i = index; i < n; i++)
        {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }

        // Move to the end of the disk (size - 1)
        TotalHeadMovement += abs(size - 1 - RQ[i - 1]);

        // Wrap around to the beginning of the disk (0)
        TotalHeadMovement += abs(size - 1 - 0);
        head = 0;

        // Service requests from left to right, in ascending order
        // Note: Do NOT use "for (i = index - 1; i >= 0; i--)" as it would reverse the order for C-SCAN
        for (i = 0; i < index; i++)
        {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }
    }

    /* If movement is towards lower values */
    else
    {
        // Move leftwards from the starting head position, servicing requests down to the smallest one
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }

        // Move to the start of the disk (0) after servicing all requests lower than the head position
        TotalHeadMovement += abs(RQ[i + 1] - 0);

        // Wrap around to the end of the disk (size - 1)
        TotalHeadMovement += abs(size - 1 - 0);
        head = size - 1;

        // Move right to left from the largest request down to the starting head position, servicing requests along the way
        for (i = n - 1; i >= index; i--)
        {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }
    }

    printf("Total head movement is %d", TotalHeadMovement);
    return 0;
}
