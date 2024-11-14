#include <stdio.h>
// optimal
int main()
{
    int pages[100], frames, n;
    int pageFaults = 0;

    // Input number of pages
    printf("Enter number of pages:\n");
    scanf("%d", &n);

    // Input page reference string
    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    // Input number of frames
    printf("Enter number of frames:\n");
    scanf("%d", &frames);

    int frame[frames];
    int index = 0;

    // Initialize frames as empty
    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1;
    }

    // Display the page reference string
    printf("Page reference string:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", pages[i]);
    }
    printf("\n\n");

    // Process each page in the reference string
    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == page)
            {
                found = 1;
                break;
            }
        }

        if (found == 0)
        {
            int farthestUse = i;
            int pageToReplace = -1;

            // Find the page to replace (optimal page replacement)
            for (int j = 0; j < frames; j++)
            {
                int nextUse = -1;

                // Look ahead to find the next use of the page
                for (int k = i + 1; k < n; k++)
                {
                    if (frame[j] == pages[k])
                    {
                        nextUse = k;
                        break;
                    }
                }

                // If the page is not used again, it is a candidate for replacement
                if (nextUse == -1)
                {
                    pageToReplace = j;
                    break;
                }

                // Otherwise, choose the page that will be used farthest in the future
                if (nextUse > farthestUse)
                {
                    farthestUse = nextUse;
                    pageToReplace = j;
                }
            }

            // Replace the page in the selected frame with the new page
            frame[pageToReplace] = page;
            pageFaults++;

            // Print the frame contents after a page fault
            printf("Page %d caused a page fault: ", page);
            for (int j = 0; j < frames; j++)
            {
                if (frame[j] == -1)
                {
                    printf(" - "); // Empty frame
                }
                else
                {
                    printf("%d ", frame[j]);
                }
            }
            printf("\n");
        }
        else
        {
            printf("Page %d did not cause a page fault.\n", page);
        }
    }

    // Output the total number of page faults
    printf("\nTotal page faults: %d\n", pageFaults);

    return 0;
}
