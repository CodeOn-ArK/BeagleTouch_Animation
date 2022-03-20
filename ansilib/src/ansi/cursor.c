#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <io.h>
#include <ansi/common.h>
#include <ansi/cursor.h>

 /*********************************************************************\
 * @fn          - point_t get_cursor_pos(void)                         *
 *                                                                     *
 * @brief       - used in getting cursor position                      *
 *                                                                     *
 * @param[n]    - void; because it only return current position        *
 *                                                                     *
 * @return      - point_t; its coordinate                              *
 *                                                                     *
 \*********************************************************************/
point_t get_cursor_pos(void)
{
    point_t ret = { 0 };
    uint32_t line, column;

    /* ESC[6n   request cursor position ( reports as ESC[#;#R ) */

    printws(NULL, CSI"6n");
    if ( scanmsg(CSI"%"PRIu32";%"PRIu32"R", &line, &column) ) {

        ret.x = column;
        ret.y = line;
    }

    return ret;
}

 /*********************************************************************\
 * @fn          - void move_cursor(point_t pos)                        *
 *                                                                     *
 * @brief       - used in moving cursor position                       *
 *                                                                     *
 * @param[n]    - point_t                                              *
 *                                                                     *
 * @return      - void; because it only moves position                 *
 *                                                                     *
 \*********************************************************************/
void move_cursor(point_t pos)
{
    /*
     * ESC[{line};{column}H
     * or
     * ESC[{line};{column}f
     */

    printws(NULL, CSI"%i;%iH", pos.y, pos.x);
}

 /*********************************************************************\
 * @fn          - void nudge_cursor(dir_t direction, uint32_t step)    *
 *                                                                     *
 * @brief       - used in pushing the cursor in specified direction    *
 *                and steps                                            *
 *                                                                     *
 * @param[n]    - dir_t; direction for cursor                          *
 *                                                                     *
 * @param[n]    - uint32_t; steps for moving the direction             *
 *                                                                     *
 * @return      - void; because it only pushes cursor                  *
 *                                                                     *
 \*********************************************************************/
void nudge_cursor(dir_t direction, uint32_t step)
{
    /* TODO: `direction` is a bitmask */
    char end_ch;

    /*
     * ESC[#A   moves cursor up # lines
     * ESC[#B   moves cursor down # lines
     * ESC[#C   moves cursor right # columns
     * ESC[#D   moves cursor left # columns
     */

    switch ( direction ) {
        case UP:    end_ch = 'A'; break;
        case DOWN:  end_ch = 'B'; break;
        case RIGHT: end_ch = 'C'; break;
        case LEFT:  end_ch = 'D';
    }

    printws(NULL, CSI"%i%c", step, end_ch);
}
