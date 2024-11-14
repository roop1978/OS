#include <stdio.h>
#include <stdlib.h>
// scan algo
int RQ[100], n, TotalHeadMovement, head, size, direction, index, i, j, temp;

int main() {
    // Input details from user
    printf("Enter the number of requests:\t");
    scanf("%d", &n);

    printf("Enter request sequence:\t");
    for(i = 0; i < n; i++) {
        scanf("%d", &RQ[i]);
    }

    printf("Enter initial head position:\t");
    scanf("%d", &head);

    printf("Enter disk size:\t");
    scanf("%d", &size);

    printf("Enter direction for movement (0 for low, 1 for high):\t");
    scanf("%d", &direction);

    // Sort the request sequence in ascending order
    for(i = 0; i < n; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(RQ[j] > RQ[j + 1]) {
                temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    // Find the starting index based on the initial head position
    for(i = 0; i < n; i++) {
        if(head < RQ[i]) {
            index = i; // initial head position
            break;
        }
    }

    // Direction handling (high or low)
    if(direction == 1) {  // Move towards high direction
        // Move to the high end (from initial head position to the last request in the sorted array)
        for(i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }
        // Move from the last request to the end of the disk
        TotalHeadMovement += abs(size - 1 - RQ[n - 1]);
        head = size - 1;

        // Move towards low direction (backwards after reaching the high end)
        for(i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }
        
    } else {  // Move towards low direction
        // Move to the low end (from initial head position to the first request in the sorted array)
        for(i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }
        TotalHeadMovement += abs(head - 0);
        head = 0;  // After servicing all low requests, move head to 0

        // Move towards high direction (move towards larger requests)
        for(i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - head);
            head = RQ[i];
        }
    }

    // Output the total head movement
    printf("Total head movement is: %d\n", TotalHeadMovement);
    return 0;
}
