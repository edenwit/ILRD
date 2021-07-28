#include <stdio.h>


#include "knights_tour.h"

#define BOARD_AXIS 8

void CreateLut();


int main ()
{
    CreateLut();

    return (0);
}


void CreateLut()
{
    static char lut[BOARD_AXIS * BOARD_AXIS][BOARD_AXIS] = {0};

    int x_move[BOARD_AXIS] = { 2, 1, -1, -2, -2, -1,  1,  2 };
    int y_move[BOARD_AXIS] = { 1, 2,  2,  1, -1, -2, -2, -1 };

    int init = 0;
    int got_to_end = 0;

    char x = 0;
    char y = 0;

    size_t i = 0;
    size_t j = 0;

    if (!init)
    {
        for (i = 0; i < BOARD_SIZE; ++i)
        {
            x = i % BOARD_AXIS;
            y = i / BOARD_AXIS;

            for (j = 0; j < BOARD_AXIS && !got_to_end; ++j)
            {
                if (x + x_move[j] >= 0 && x + x_move[j] < BOARD_AXIS
                    && y + y_move[j] >= 0 && y + y_move[j] < BOARD_AXIS)
                {
                    lut[i][j] = x + x_move[j] + (y + y_move[j]) * BOARD_AXIS;
                }
                else
                {
                    lut[i][j] = -1;
                    got_to_end = 1;
                }
            }
            for (j;j < BOARD_AXIS; ++i)
            got_to_end = 0;
        }


        init = 1;
    }
    printf("{");
    for (i = 0; i < BOARD_SIZE; ++i)
    {       printf("{");
            for (j = 0; j < BOARD_AXIS; ++j)
            {
                printf("%d", lut[i][j]);

                if (j != BOARD_AXIS -1)
                {
                    printf(", ");
                }

            }
            printf("}");
            if (i != BOARD_SIZE -1)
            {
                printf(", ");
            }
        printf("\n");

    }
    printf("}\n");

    return;
}
