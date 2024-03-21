/**
 * ECE361_HW1_Prob3.c count items in nursery rhyme style
 *
 * @author: Phil Nevins (pnevins@pdx.edu)
 * @date: 7-OCT-2023
 *
 * This program counts up and down items in a nursery rhyme style. This includes
 * Part a & b
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#define NITEMS 10

void displayCountUp(int count, char thing[], int MaxCountUp);
void displayCountDown(int count, char thing[], int MaxCountDown);

main ()
{
    // greet the user and display the working directory for the application
    // this code should be included in all of the applications you submit for ECE 361
    printf("ECE361_HW1_Prob3 - Count up/down nursery rhyme generator by Phil Nevins (pnevins@pdx.edu)\n");
    errno = 0;
    char *buf = getcwd(NULL, 0);    // allocates a buffer large enough to hold the path

    if (buf == NULL) {
        perror("getcwd");
        printf("Could not display the path\n");
    }
    else {
        printf("Current working directory: %s\n", buf);
        free(buf);
    }
    printf("\n");

//Count Up & Down function calls
    displayCountUp(1, "spider", NITEMS);
    printf("\n");
    displayCountDown(10, "spider", 1);


}

//Count Up Function
void displayCountUp(int count, char thing[], int MaxCountUp)
{
    for (count; count <= MaxCountUp; count++)
    {
        if (count % 3 == 0)
            printf ("%i little %ss\n", count, thing);
        else if (count == MaxCountUp)
            printf ("%i little %s bugs\n", count, thing);
        else
            printf ("%i little, ", count);
    }
}

//Count Down Function
void displayCountDown(int count, char thing[], int MaxCountDown)
{
    for (count; count >= MaxCountDown; count--)
    {
        if ((count+1) % 3 == 0)
            printf ("%i little %ss\n", count, thing);
        else if (count == 1)
            printf ("%i little %s bugs", count, thing);
        else
            printf ("%i little, ", count);
    }
}