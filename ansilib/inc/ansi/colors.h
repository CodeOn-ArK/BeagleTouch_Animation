#ifndef __ANSI_COLORS_H_
# define __ANSI_COLORS_H_

# define DONT_CHANGE 0

 /*********************************************************************\
 * @brief   - Summarizing the colors for background and foreground     *
 *            text                                                     *
 *                                                                     *
 \*********************************************************************/
typedef enum {
    /* DONT_CHANGE=0, */

    /* Foreground colors */
    BLACK_FG=30,
    RED_FG,
    GREEN_FG,
    YELLOW_FG,
    BLUE_FG,
    MAGENTA_FG,
    CYAN_FG,
    WHITE_FG,
    /* No 38, eh? */
    DEFAULT_FG=39,

    /* Background colors */
    BLACK_BG=40,
    RED_BG,
    GREEN_BG,
    YELLOW_BG,
    BLUE_BG,
    MAGENTA_BG,
    CYAN_BG,
    WHITE_BG,
    /* No 48 either, eh? */
    DEFAULT_BG=49,

    /* Bright Foreground colors */
    BRIGHT_BLACK_FG=90,
    BRIGHT_RED_FG,
    BRIGHT_GREEN_FG,
    BRIGHT_YELLOW_FG,
    BRIGHT_BLUE_FG,
    BRIGHT_MAGENTA_FG,
    BRIGHT_CYAN_FG,
    BRIGHT_WHITE_FG,

    /* Bright Background colors */
    BRIGHT_BLACK_BG=100,
    BRIGHT_RED_BG,
    BRIGHT_GREEN_BG,
    BRIGHT_YELLOW_BG,
    BRIGHT_BLUE_BG,
    BRIGHT_MAGENTA_BG,
    BRIGHT_CYAN_BG,
    BRIGHT_WHITE_BG,
} color_t;

 /********************************************************************\
 * @brief   - Summarizing the styles for background and foreground    *
 *            text                                                    *
 *                                                                    *
 \********************************************************************/
typedef enum {
    /* DONT_CHANGE = 0, */
    BOLD        = (1 << 0),
    FAINT       = (1 << 1),
    ITALIC      = (1 << 2),
    UNDERLINE   = (1 << 3),
    BLINKING    = (1 << 4),
    INVERSE     = (1 << 5),
    INVISIBLE   = (1 << 6),
    STRIKE      = (1 << 7),
} text_mode_t;

#endif  /* __ANSI_COLORS_H_ */
