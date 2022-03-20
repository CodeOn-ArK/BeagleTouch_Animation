#include <stdint.h>
#include <stdlib.h>

#include <ansi/cursor.h>
#include <graphics/box.h>
#include <graphics/shapes.h>

 /*********************************************************************\
 * @fn          - void draw(const box_t *box)                          *
 *                                                                     *
 * @brief       - draws a box                                          *
 *                                                                     *
 * @param[in]   - box_t; covers the properties of a box                *
 *                                                                     *
 * @return      - void                                                 *
 \*********************************************************************/
void draw(const box_t *box)
{
    switch ( box->type ) {
    case RECTANGLE:
        move_cursor(box->origin);
        draw_rectangle(&box->border, &box->fill, box->width, box->height,
                       box->border_ch, box->fill_ch);
        break;
    case TRIANGLE:
        move_cursor(box->origin);
        draw_triangle(&box->border, &box->fill, box->height,
                      box->border_ch, box->fill_ch);
        break;
    }
}

 /*********************************************************************\
 * @fn          - void erase(const box_t *box)                         *
 *                                                                     *
 * @brief       - erases a box                                         *
 *                                                                     *
 * @param[n]    - box_t                                                *
 *                                                                     *
 * @return      - void                                                 *
 \*********************************************************************/
void erase(const box_t *box)
{
    switch ( box->type ) {
    case RECTANGLE:
        move_cursor(box->origin);
        draw_rectangle(NULL, NULL, box->width, box->height, ' ', ' ');
        break;
    case TRIANGLE:
        move_cursor(box->origin);
        draw_triangle(NULL, NULL, box->height, ' ', ' ');
        break;
    }
}

 /*********************************************************************\
 * @fn               - void                                            *
 *                     nudge(box_t *box, dir_t dir, int32_t steps)     *
 *                                                                     *
 * @brief            - draws the shape according to direction and      *
 *                     steps                                           *
 *                                                                     *
 * @param[n]         - box_t; covers the properties of a box           *
 * @param[n]         - dir_t; nudge direction                          *
 * @param[n]         - int32_t; steps in the specified direction       *
 *                                                                     *
 * @return           - void                                            *
 \*********************************************************************/
void nudge(box_t *box, dir_t dir, int32_t steps)
{
    switch ( dir ) {
    case UP:
        box->origin.y -= steps;
        break;

    case DOWN:
        box->origin.y += steps;
        break;

    case LEFT:
        box->origin.x -= steps;
        break;

    case RIGHT:
        box->origin.x += steps;
        break;
    }
}
