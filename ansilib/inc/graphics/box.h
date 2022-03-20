#ifndef __GRAPHICS_BOX_H_
# define __GRAPHICS_BOX_H_

# include <graphics/common.h>
# include <ansi/style.h>

 /*********************************************************************\
 * @brief   - Defining the shapes included                             *
 *                                                                     *
 \*********************************************************************/
typedef enum {
    RECTANGLE,
    TRIANGLE,
} shape_t;

typedef struct {
    shape_t type;
    point_t origin;
    style_t border, fill;
    uint32_t width, height;
    char border_ch, fill_ch;
} box_t;

void draw(const box_t *box);
void erase(const box_t *box);
void nudge(box_t *box, dir_t dir, int32_t steps);

#endif  /* __GRAPHICS_BOX_H_ */
