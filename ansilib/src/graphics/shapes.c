#include <stddef.h>

#include <io.h>
#include <ansi/cursor.h>
#include <ansi/style.h>
#include <graphics/shapes.h>

 /*********************************************************************\
 * @fn          - void draw_rectangle(const style_t *border,           *
 *                                    const style_t *fill,             *
 *                                    uint32_t width, uint32_t height, *
 *                                    char ch, char fill_ch)           *
 *                                                                     *
 * @brief       - draws a rectangle                                    *
 *                                                                     *
 * @param[n]    - style_t; color and style of border and inner         *
 *                         characters                                  *
 * @param[n]    - uint32_t; height and width                           *
 * @param[n]    - char; character for inner and border                 *
 *                                                                     *
 * @return      - void                                                 *
 *                                                                     *
 \*********************************************************************/
void draw_rectangle(const style_t *border, const style_t *fill,
                    uint32_t width, uint32_t height, char ch, char fill_ch)
{
    /* Top edge */
    for (uint32_t i = 0; i < width; i++) {
        /* TODO: Let's not forget about `border_width` */
        printws(border, "%c", ch);
    }

    for (uint32_t i = 0; i < height - 2; i++) {

        /* Get to the next line */
        nudge_cursor(LEFT, width);
        nudge_cursor(DOWN, 1);

        /* Left edges */
        printws(border, "%c", ch);

        /* Filling internal colour */
        if(fill_ch != '\0')
            for (uint32_t i = 0; i < width - 2; i++)
                printws(fill, "%c", fill_ch);

        /* Right edges */
        printws(border, "%c", ch);
    }

    /* Get to the next line */
    nudge_cursor(LEFT, width);
    nudge_cursor(DOWN, 1);

    /* Bottom edge */
    for (uint32_t i = 0; i < width; i++) {
        printws(border, "%c", ch);
    }
}

 /*********************************************************************\
 * @fn          - void draw_triangle(const style_t *border,            *
 *                                   const style_t *fill,              *
 *                                   uint32_t height, char ch,         *
 *                                   char fill_ch)                     *
 *                                                                     *
 * @brief       - draws a triangle                                     *
 *                                                                     *
 * @param[n]    - style_t                                              *
 * @param[n]    - uint32_t                                             *
 * @param[n]    - char                                                 *
 *                                                                     *
 * @return      - void                                                 *
 *                                                                     *
 \*********************************************************************/
void draw_triangle(const style_t *border, const style_t *fill,
                   uint32_t height, char ch, char fill_ch)
{
    /*  Draws a triangle, on the basis of height   */

    for (uint32_t i = 0; i < height - 1; i++) {

        /* right arm*/
        printws(border , "%c", ch);
        nudge_cursor(DOWN, 1);

    }

    /* Bottom side  */
    nudge_cursor(LEFT, 2*(height-1) );
    for(uint32_t i = 2*(height - 1) +1 ; i > 0; i--)
        printws(border, "%c", ch);
    nudge_cursor(LEFT, 2*(height-1) + 1);

    for (uint32_t i = 0; i < height - 1; i++) {

        /* left arm*/
        printws(border, "%c", ch);
        nudge_cursor(UP, 1);

    }

    uint32_t temp = 1;
    nudge_cursor(DOWN, 1);

    /* Filling internal colour */
    for (uint32_t i = 0; i < height - 2; i++) {

        for (uint32_t j = 0; j < 2*temp - 1; j++)
            printws(fill, "%c", fill_ch);

        nudge_cursor(DOWN, 1);
        nudge_cursor(LEFT, 2*temp);
        temp++;

    }
}
