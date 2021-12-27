
#include <stdio.h>
#define MAX 99999

int no_frames, no_Reference, front = 1, no_pfaults;

int initializing(int PageFrame[])
{
    int x;
    for (x = 0; x < no_frames; x++)
        PageFrame[x] = -1;
    return 0;
}

int search(int Array[], int element, int m)
{
    int y;
    for (y = 0; y < m; y++)
    {
        if (Array[y] == element)
            return 1;
    }
    return -1;
}

int DisplayFaults(int PageFrame[])
{
    int z = 0;
    for (z = 0; z < no_frames; z++)
    {
        printf("|%d", PageFrame[z]);
    }
    printf("|\n\n");
}
int left_subtract1(int Arr[])
{
    int j = 0, position = -1;
    for (j = 0; j < no_frames; j++)
    {
        if (Arr[j] == -1)
        {
            position = j;
            break;
        }
    }
    return (position);
}

int FIFO(int PageFrame[], int PageReference[])
{
    initializing(PageFrame);
    no_pfaults = 0;
    int x, element;
    for (x = 0; x < no_Reference; x++)
    {
        element = PageReference[x];
        if (search(PageFrame, element, no_frames) == -1)
        {
            printf(" %d - Miss\n", element);
            no_pfaults++;

            PageFrame[front - 1] = element;
            DisplayFaults(PageFrame);
            front = front % (no_frames) + 1;
        }
        else
        {
            printf(" %d - Hit\n", element);
            DisplayFaults(PageFrame);
        }
    }
    printf(" Total number of page faults : %d\n", no_pfaults);
    return 0;
}
int optimal(int PageFrame[], int PageReference[])
{
    initializing(PageFrame);
    no_pfaults = 0;
    int a, b, c, element, found, n;  //i j k x
    int ToBe_used[no_frames];
    for (a = 0; a < no_frames; a++)
    {
        ToBe_used[a] = -1;
    }
    for (a = 0; a < no_Reference; a++)
    {
        if (search(PageFrame, PageReference[a], no_frames) == -1)
        {
            n = left_subtract1(PageFrame);
            //printf("\nx : %d\n", x);
            if (n== -1)
            {
                //printf(" %d - Miss\n", pageRef[i]);
                for (b= 0; b< no_frames; b++)
                {
                    int element = PageFrame[b];
                    found = 0;
                    for (c= a+ 1; c< no_Reference; c++)
                    {
                        if (element == PageReference[c])
                        {
                            ToBe_used[b] = c;
                            found = 1;
                            break;
                        }
                        else
                            found = 0;
                    }
                    if (!found)
                        ToBe_used[b] = -1;
                }
                int maximum = -32767;
                int ElementIndex;
                for (b = 0; b < no_frames; b++)
                {
                    if (ToBe_used[b] == -1)
                    {
                        maximum = ToBe_used[b];
                        ElementIndex = b;
                        break;
                    }
                    if (ToBe_used[b] > maximum)
                    {
                        maximum = ToBe_used[b];
                        ElementIndex = b;
                    }
                }

                PageFrame[ElementIndex] = PageReference[a];
                no_pfaults++;
                printf(" %d - Miss\n", PageReference[a]);
                DisplayFaults(PageFrame);
            }
            else
            {
                PageFrame[n] = PageReference[a];
                no_pfaults++;
                printf(" %d - Miss\n", PageReference[a]);
                DisplayFaults(PageFrame);
            }
        }
        else
        {
            printf(" %d - Hit\n", PageReference[a]);
            DisplayFaults(PageFrame);
        }
    }
    printf(" Total number of page faults : %d\n", no_pfaults);
    return 0;
}
int lru(int PageFrame[], int PageReference[])
{
    initializing(PageFrame);
    no_pfaults = 0;
    int a, b, c, element, found; // i j k 
    int less_used[no_frames];
    for (a = 0; a < no_Reference; a++)
    {
        if (search(PageFrame, PageReference[a], no_frames) == -1)
        {
            //printf(" %d - Miss\n", pageRef[i]);
            for (b = 0; b < no_frames; b++)
            {
                int element = PageFrame[b];
                found = 0;
                for (c = a - 1; c >= 0; c--)
                {
                    if (element == PageReference[c])
                    {
                        less_used[b] = c;
                        found = 1;
                        break;
                    }
                    else
                        found = 0;
                }
                if (!found)
                    less_used[b] = -1;
            }
            int minimum = MAX;
            int ElementIndex;
            for (b = 0; b < no_frames; b++)
            {
                if (less_used[b] < minimum)
                {
                    minimum = less_used[b];
                    ElementIndex = b;
                }
            }
            PageFrame[ElementIndex] = PageReference[a];
            no_pfaults++;
            printf(" %d - Miss\n", PageReference[a]);
            DisplayFaults(PageFrame);
        }
        else
        {

            printf(" %d - Hit\n", PageReference[a]);
            DisplayFaults(PageFrame);
        }
    }
    printf(" Total number of page faults : %d\n", no_pfaults);
    return 0;
}
int main()
{
    int a;
    int choice;
    printf("\n Enter 1:FIFO  2:Optimal  3:LRU: ");
    scanf("%d", &choice);
    printf("\n Enter number of page frames : ");
    scanf("%d", &no_frames);
    int PageFrame[no_frames];
    printf(" Enter number of page references : ");
    scanf("%d", &no_Reference);
    int PageReference[no_Reference];
    printf(" Enter the page references : \n");
    for (a = 0; a < no_Reference; a++)
        scanf("%d", &PageReference[a]);
    if (choice==1){
    printf("\n FIFO Page Replacement Algorithm : \n");
    FIFO(PageFrame, PageReference);
        
    }
    else if (choice==2){
    printf("\n Optimal Page Replacement Algorithm : \n");
    optimal(PageFrame, PageReference);
        
    }
    else {
    printf("\n LRU Page Replacement Algorithm : \n");
    lru(PageFrame, PageReference);
    }
    return 0;
}
