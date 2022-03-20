#ifndef __GRAPHICS_COMMON_H_
# define __GRAPHICS_COMMON_H_

#include <stdint.h>

 /*********************************************************************\
 * @brief   - Declaring the position coordinates of cursor or origin   *
 *            of a box.                                                *
 *                                                                     *
 \*********************************************************************/
typedef struct {
    int32_t x, y;
} point_t;

point_t point(int32_t x, int32_t y);

#endif  /* __GRAPHICS_COMMON_H_ */
