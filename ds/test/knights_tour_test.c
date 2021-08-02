#include <stdio.h>
#include <time.h>   /* time_t */
#include <stdlib.h> /* rand */

#include "knights_tour.h"

#define BOARD_AXIS 8

static void CreateTourTest(size_t start_position);
static void CreateWarnsdorffsTourTest(size_t start_position);

static void PrintBoard(char *path);

int main()
{
    char rando = 0;
    size_t i = 0;

    srand(time(0));
    rando = (rand() % BOARD_SIZE);

    for (i = 0; i < BOARD_SIZE; ++i)
    {
        /* CreateTourTest(i); */
        CreateWarnsdorffsTourTest(i);
    }

    /*     CreateTourTest(0);
    CreateTourTest(rando);

    CreateWarnsdorffsTourTest(rando); */

    return (0);
}

static void CreateTourTest(size_t start_position)
{
    char path[BOARD_SIZE] = {0};

    time_t start_time = time(NULL);

    printf("\nTrying Knights Tour from square %ld within %d seconds:\n", start_position, 3600);

    CreateTour(start_position, path);

    PrintBoard(path);

    printf("Total time: %f\n", difftime(time(NULL), start_time));
}

static void CreateWarnsdorffsTourTest(size_t start_position)
{
    char path[BOARD_SIZE] = {0};

    time_t start_time = time(NULL);

    printf("\nTrying Warnsdorffs Knights Tour from square %ld within %d seconds:\n", start_position, 3600);

    if (0 == WarnsdorffsTour(start_position, path))
    {
        PrintBoard(path);
    }

    printf("Total time: %f\n", difftime(time(NULL), start_time));
}

static void PrintBoard(char *path)
{
    size_t i = 0;

    for (i = 0; i < BOARD_SIZE; ++i)
    {

        if (0 == i % BOARD_AXIS)
        {
            printf("\n");
        }
        printf("%d ", path[i]);
    }

    printf("\n\n");
}
