#ifndef __ANSI_CURSOR_H_
# define __ANSI_CURSOR_H_

# include <graphics/common.h>

 /*********************************************************************\
 * @brief   - Defining the nudge direction of the cursor for           *
 *            positioning of the texts                                 *
 *                                                                     *
 \*********************************************************************/
typedef enum { LEFT, DOWN, UP, RIGHT } dir_t;

point_t get_cursor_pos(void);
void move_cursor(point_t);
void nudge_cursor(dir_t, uint32_t step);

#endif  /* __ANSI_CURSOR_H_ */
