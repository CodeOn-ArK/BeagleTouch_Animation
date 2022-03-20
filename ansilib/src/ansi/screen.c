#include <stddef.h>

#include <io.h>
#include <ansi/common.h>
#include <ansi/cursor.h>
#include <ansi/screen.h>

 /*********************************************************************\
 * @fn          - screen_t get_screen_size(void)                       *
 *                                                                     *
 * @brief       - fetches the lines and columns of the terminal        *
 *                                                                     *
 * @param[n]    - void; because it only return screen size             *
 *                                                                     *
 * @return      - screen_t; rows and columns                           *
 *                                                                     *
 \*********************************************************************/
screen_t get_screen_size(void)
{
    screen_t ret;
    point_t orig_pos = get_cursor_pos(), temp;

    /* Quoting from
     * https://viewsourcecode.org/snaptoken/kilo/03.rawInputAndOutput.html#window-size-the-hard-way
     *
     * We use a very large value, 999, which should ensure that the
     * cursor reaches the right and bottom edges of the screen.
     *
     * The C and B commands are specifically documented to stop the
     * cursor from going past the edge of the screen. The reason we
     * don’t use the <esc>[999;999H command is that the documentation
     * doesn’t specify what happens when you try to move the cursor
     * off-screen.
     */
    nudge_cursor(RIGHT, 999);
    nudge_cursor(DOWN, 999);
    temp =  get_cursor_pos();
    ret.cols  = (uint32_t) temp.x;
    ret.lines = (uint32_t) temp.y;

    move_cursor(orig_pos);
    return ret;
}

 /*********************************************************************\
 * @fn          - void clear_screen(void)                              *
 *                                                                     *
 * @brief       - clears the terminal screen                           *
 *                                                                     *
 * @param[n]    - void                                                 *
 *                                                                     *
 * @return      - void                                                 *
 *                                                                     *
 \*********************************************************************/
void clear_screen(void)
{
    printws(NULL, CSI"H"CSI"2J");
}

