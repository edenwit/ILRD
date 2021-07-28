#ifndef _RD_102_KNIGHTS_TOUR_H_
#define _RD_102_KNIGHTS_TOUR_H_

#include <stddef.h>     /* size_t */

 typedef enum return_val
 { 
    SUCCESS,
    TIME_OUT
    /*more... */
 } return_val_t;

#define BOARD_SIZE (64)

int CreateTour(char start_position, char path[BOARD_SIZE]);
int WarnsdorffsTour(char start_position, char path[BOARD_SIZE]);



/*
    wan.. algorythm - GetMinDegreeStep: Successor is the step that has the smallest num of neighbors.
    is_in_chess_borders 
    is_allready_visited_spot

    advanced: add graphics
*/

#endif /* _RD_102_KNIGHTS_TOUR_H_ */

