#ifndef __ANSI_SCREEN_H_
# define __ANSI_SCREEN_H_

# include <graphics/common.h>

 /*********************************************************************\
 * @brief   - Declaring the columns and rows for screen                *
 *                                                                     *
 \*********************************************************************/
typedef struct {
    uint32_t cols, lines;
} screen_t;

screen_t get_screen_size(void);
void clear_screen(void);

#endif  /* __ANSI_SCREEN_H_ */
