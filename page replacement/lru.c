#include <stdio.h>

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
    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1; // Initialize frames as empty
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

        // Check if the page is already in one of the frames
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == page)
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            // Page fault: need to replace a page
            int lru_index = -1;
            int farthest = i; // Set farthest to the current index

            // Find the LRU page (least recently used)
            for (int j = 0; j < frames; j++)
            {
                int found_in_future = 0;
                for (int k = i + 1; k < n; k++)
                {
                    if (frame[j] == pages[k])
                    {
                        found_in_future = 1;
                        if (k > farthest)
                        {
                            farthest = k;
                            lru_index = j;
                        }
                        break;
                    }
                }

                // If the page was not found in the future, it is the LRU
                if (!found_in_future)
                {
                    lru_index = j;
                    break;
                }
            }

            // Replace the LRU page with the new page
            frame[lru_index] = page;
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
