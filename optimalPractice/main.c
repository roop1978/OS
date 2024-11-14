#include <stdio.h>
#include <stdlib.h>

int main()
{
    int pages[100], n, frames;
    int pageFaults = 0;

    // Input number of pages
    printf("Enter number of pages:\n");
    scanf("%d", &n);

    // Input page reference string
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input number of frames
    printf("Enter number of frames:\n");
    scanf("%d", &frames);

    // Declare frame array to store the pages currently in memory
    int frameArray[frames];

    // Initialize frames as empty (-1 means empty)
    for (int i = 0; i < frames; i++) {
        frameArray[i] = -1; // Corrected initialization of the frame array
    }

    // Display the page reference string (for clarity)
    printf("Page reference string:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t", pages[i]);
    }
    printf("\n\n");

    // Process each page in the reference string
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < frames; j++) {
            if (frameArray[j] == page) { // Corrected frame reference
                found = 1;
                break;
            }
        }

        if (found == 0) { // If page is not found in any frame, page fault occurs
            int farthestUse = i;
            int pageToReplace = -1;

            // Find the page to replace (optimal page replacement)
            for (int j = 0; j < frames; j++) {
                int nextUse = -1;

                // Look ahead to find the next use of the page
                for (int k = i + 1; k < n; k++) {
                    if (frameArray[j] == pages[k]) { // Corrected frame reference
                        nextUse = k;
                        break;
                    }
                }

                // If the page is not used again, it is a candidate for replacement
                if (nextUse == -1) {
                    pageToReplace = j;
                    break;
                }

                // Otherwise, choose the page that will be used farthest in the future
                if (nextUse > farthestUse) {
                    farthestUse = nextUse;
                    pageToReplace = j;
                }
            }

            // Replace the page in the selected frame with the new page
            frameArray[pageToReplace] = page; // Corrected frame reference
            pageFaults++;

            // Print the frame contents after a page fault
            printf("Page %d caused a page fault: ", page);
            for (int j = 0; j < frames; j++) {
                if (frameArray[j] == -1) { // Corrected frame reference
                    printf(" - "); // Empty frame
                } else {
                    printf("%d ", frameArray[j]); // Corrected frame reference
                }
            }
            printf("\n");
        } else {
            printf("Page %d did not cause a page fault.\n", page);
        }
    }

    // Output the total number of page faults
    printf("\nTotal page faults: %d\n", pageFaults);

    return 0;
}
