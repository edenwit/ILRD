#include <pthread.h> /* pthred_create */
#include <assert.h>  /* assert */
#include <unistd.h>  /* sleep */
#include <stdio.h>   /* printf */
#include <stdlib.h>

#include "knights_tour.h"
#include "bit_array.h"

#define BOARD_AXIS 8
#define TIMER_SECONDS 3600
#define UNUSED(X) ((void)X)

typedef struct position_with_possibilities
{
    char position;
    size_t possibilities;
} position_with_possibilities_t;

int timed_out = 0;

/* knights tour funcs */
static return_val_t RecGoToNext(bit_arr_t chess_board, char curr_position,
                                char *path);
static char GetNextAvalableStep(char position, size_t move);

/* knights tour funcs */
static return_val_t RecWarnsdorffsGoToNext(bit_arr_t chess_board,
                                           char curr_position, char *path);
static size_t GetDegrees(bit_arr_t chess_board, char curr_position);
static int CmpFunc(const void *data1, const void *data2);
static void InitAndSortPosArr(bit_arr_t chess_board, char curr_position,
                              position_with_possibilities_t *arr);

/* timeout funcs */
static void *TimeOutClock(void *param);

int CreateTour(char start_position, char path[BOARD_SIZE])
{
    bit_arr_t chess_board = 0;
    pthread_t thread = {0};

    assert(0 <= start_position && BOARD_SIZE > start_position);

    pthread_create(&thread, NULL, &TimeOutClock, NULL);

    if (TIME_OUT == RecGoToNext(chess_board, start_position, path))
    {
        printf("Timed out\n");
        return (1);
    }

    pthread_cancel(thread);

    return (0);
}

int WarnsdorffsTour(char start_position, char path[BOARD_SIZE])
{
    bit_arr_t chess_board = 0;
    pthread_t thread = {0};

    assert(0 <= start_position && BOARD_SIZE > start_position);

    pthread_create(&thread, NULL, &TimeOutClock, NULL);

    if (TIME_OUT == RecWarnsdorffsGoToNext(chess_board, start_position, path))
    {
        printf("Timed out\n");
        return (1);
    }

    pthread_cancel(thread);

    return (0);
}

static return_val_t RecGoToNext(bit_arr_t chess_board, char curr_position, 
                                char *path)
{
    size_t i = 0;
    int status = -1;

    if (1 == timed_out)
    {
        return (TIME_OUT);
    }

    if (BOARD_SIZE == BitArrCountOn(chess_board))
    {
        return (SUCCESS);
    }

    path[BitArrCountOn(chess_board)] = curr_position;

    for (i = 0; i < BOARD_AXIS && -1 == status; ++i)
    {
        if ((-1 != curr_position) 
            && (1 != BitArrGetVal(chess_board, curr_position)))
        {
            status = RecGoToNext(BitArrSetOn(chess_board, curr_position),
                                 GetNextAvalableStep(curr_position, i), path);
        }
    }

    return (status);
}

static void InitAndSortPosArr(bit_arr_t chess_board, char curr_position,
                              position_with_possibilities_t *arr)
{
    size_t i = 0;

/*     for (i = 0; i < BOARD_AXIS; ++i)
    {
        printf("(%d, %d, %d) ", curr_position, (arr + i)->position, (arr + i)->possibilities);
    } */
    for (i = 0; i < BOARD_AXIS; ++i)
    {
        (arr + i)->position = GetNextAvalableStep(curr_position, i);
        (arr + i)->possibilities = GetDegrees(BitArrSetOn(chess_board, curr_position), (arr + i)->position);
    }

/*     printf("\n");

    sleep(1); */

    qsort(arr, BOARD_AXIS, sizeof(position_with_possibilities_t), CmpFunc);

/*      for (i = 0; i < BOARD_AXIS; ++i)
    {
        printf("(%d, %d, %d) ", curr_position, (arr + i)->position, (arr + i)->possibilities);
    }
    printf("\n");

        sleep(1);  */

    return;
}

static size_t GetDegrees(bit_arr_t chess_board, char curr_position)
{
    size_t i = 0;
    size_t j = 0;
    size_t counter = 0;
    char next_position = 0;

/*     printf("\ncheckig steps for %d\n", curr_position);
 */
    if (-1 == curr_position)
    {
        return (0);
    }

    for (j = 0; j < BOARD_AXIS; ++j)
    {
        next_position = GetNextAvalableStep(curr_position, j);
/*         printf("checking for %d\n", next_position);
 */
        if ((-1 != next_position) && (0 == BitArrGetVal(chess_board, next_position)))
        {
/*             printf("for %d: %d, %d\n",next_position, (-1 != next_position) , (0 == BitArrGetVal(chess_board, next_position)));
 */            ++counter;
        }
        
    }

    return (counter);
}

static return_val_t RecWarnsdorffsGoToNext(bit_arr_t chess_board, 
                                           char curr_position, char *path)
{
    position_with_possibilities_t pos_arr[BOARD_AXIS] = {0};
    size_t i = 0;
    int status = STUCK;

    if (1 == timed_out)
    {
        return (TIME_OUT);
    }

    if (BOARD_SIZE == BitArrCountOn(chess_board))
    {
        return (SUCCESS);
    }

    InitAndSortPosArr(chess_board, curr_position, pos_arr);

    path[BitArrCountOn(chess_board)] = curr_position;

    for (i = 0;( i < BOARD_AXIS) && (STUCK == status); ++i)
    {
        if ((-1 != curr_position) && (0 != (pos_arr + i)->possibilities) 
            && (1 != BitArrGetVal(chess_board, curr_position)))
        {
            status = RecWarnsdorffsGoToNext(BitArrSetOn(chess_board, curr_position),
                                            (pos_arr + i)->position, path);
        }
    }

    return (status);
}


static char GetNextAvalableStep(char position, size_t move)
{
    static char lut[BOARD_SIZE][BOARD_AXIS] =
        {{10, 17, -1, -1, -1, -1, -1, -1},
         {11, 18, 16, -1, -1, -1, -1, -1},
         {12, 19, 17, 8, -1, -1, -1, -1},
         {13, 20, 18, 9, -1, -1, -1, -1},
         {14, 21, 19, 10, -1, -1, -1, -1},
         {15, 22, 20, 11, -1, -1, -1, -1},
         {23, 21, 12, -1, -1, -1, -1, -1},
         {22, 13, -1, -1, -1, -1, -1, -1},
         {18, 25, 2, -1, -1, -1, -1, -1},
         {19, 26, 24, 3, -1, -1, -1, -1},
         {20, 27, 25, 16, 0, 4, -1, -1},
         {21, 28, 26, 17, 5, 1, -1, -1},
         {22, 29, 27, 18, 2, 6, -1, -1},
         {23, 30, 28, 19, 3, 7, -1, -1},
         {31, 29, 20, 4, -1, -1, -1, -1},
         {30, 21, 5, -1, -1, -1, -1, -1},
         {26, 33, 1, 10, -1, -1, -1, -1},
         {27, 34, 32, 0, 2, 11, -1, -1},
         {28, 35, 33, 24, 8, 1, 3, 12},
         {29, 36, 34, 25, 9, 2, 4, 13},
         {30, 37, 35, 26, 10, 3, 5, 14},
         {31, 38, 36, 27, 11, 4, 6, 15},
         {39, 37, 28, 12, 5, 7, -1, -1},
         {38, 29, 13, 6, -1, -1, -1, -1},
         {34, 41, 9, 18, -1, -1, -1, -1},
         {35, 42, 40, 8, 10, 19, -1, -1},
         {36, 43, 41, 32, 16, 9, 11, 20},
         {37, 44, 42, 33, 17, 10, 12, 21},
         {38, 45, 43, 34, 18, 11, 13, 22},
         {39, 46, 44, 35, 19, 12, 14, 23},
         {47, 45, 36, 20, 13, 15, -1, -1},
         {46, 37, 21, 14, -1, -1, -1, -1},
         {42, 49, 17, 26, -1, -1, -1, -1},
         {43, 50, 48, 16, 18, 27, -1, -1},
         {44, 51, 49, 40, 24, 17, 19, 28},
         {45, 52, 50, 41, 25, 18, 20, 29},
         {46, 53, 51, 42, 26, 19, 21, 30},
         {47, 54, 52, 43, 27, 20, 22, 31},
         {55, 53, 44, 28, 21, 23, -1, -1},
         {54, 45, 29, 22, -1, -1, -1, -1},
         {50, 57, 25, 34, -1, -1, -1, -1},
         {51, 58, 56, 24, 26, 35, -1, -1},
         {52, 59, 57, 48, 32, 25, 27, 36},
         {53, 60, 58, 49, 33, 26, 28, 37},
         {54, 61, 59, 50, 34, 27, 29, 38},
         {55, 62, 60, 51, 35, 28, 30, 39},
         {63, 61, 52, 36, 29, 31, -1, -1},
         {62, 53, 37, 30, -1, -1, -1, -1},
         {58, 33, 42, -1, -1, -1, -1, -1},
         {59, 32, 34, 43, -1, -1, -1, -1},
         {60, 56, 40, 33, 35, 44, -1, -1},
         {61, 57, 41, 34, 36, 45, -1, -1},
         {62, 58, 42, 35, 37, 46, -1, -1},
         {63, 59, 43, 36, 38, 47, -1, -1},
         {60, 44, 37, 39, -1, -1, -1, -1},
         {61, 45, 38, -1, -1, -1, -1, -1},
         {41, 50, -1, -1, -1, -1, -1, -1},
         {40, 42, 51, -1, -1, -1, -1, -1},
         {48, 41, 43, 52, -1, -1, -1, -1},
         {49, 42, 44, 53, -1, -1, -1, -1},
         {50, 43, 45, 54, -1, -1, -1, -1},
         {51, 44, 46, 55, -1, -1, -1, -1},
         {52, 45, 47, -1, -1, -1, -1, -1},
         {53, 46, -1, -1, -1, -1, -1, -1}};

    return (lut[(size_t)position][move]);
}

void *TimeOutClock(void *param)
{
    size_t remain = TIMER_SECONDS;

    UNUSED(param);

    while (0 < remain)
    {
        remain = sleep(remain);
    }

    timed_out = 1;

    return (0);
}

int CmpFunc(const void *data1, const void *data2)
{
    return (((position_with_possibilities_t *)(data2))->possibilities - ((position_with_possibilities_t *)(data1))->possibilities);
}