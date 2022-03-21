  /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
  *                                                                                       *
  | Copyright (C) 2022 CodeOn-ArK@github                                                  |
  *                                                                                       *
  | This program is free software: you can redistribute it and/or modify                  |
  * it under the terms of the GNU General Public License as published by                  *
  | the Free Software Foundation, either version 3 of the License, or                     |
  * (at your option) any later version.                                                   *
  |                                                                                       |
  * This program is distributed in the hope that it will be useful,                       *
  | but WITHOUT ANY WARRANTY; without even the implied warranty of                        |
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                         *
  | GNU General Public License for more details.                                          |
  *                                                                                       *
  | You should have received a copy of the GNU General Public License                     |
  * along with this program.  If not, see <https://www.gnu.org/licenses/>.                *
  |                                                                                       |
  **-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

#include "main.h"

int fd;
int buf[2] = {0};
struct termios orig_termios;    /* Keeps the original attributes */
uint32_t MAX_COLS,MAX_ROWS ;


static inline void enable_raw_mode(void)
{
    struct termios raw;

    atexit(disable_raw_mode);   /* defer call to disable_raw_mode() */

    /* Fetch the current attributes and keep a copy */
    tcgetattr(STDIN_FILENO, &orig_termios);
    raw = orig_termios;

    /* turn off a bunch of things:
     *      BRKINT  : send SIGINT on break
     *      ICRNL   : translation of '\r' to '\n'
     *      INPCK   : parity checking
     *      ISTRIP  : strip 8th bit of every input byte
     *      IXON    : software flow control (^S and ^Q)
     *      OPOST   : translation of "\n" to "\r\n"
     *      ECHO    : echoing of characters
     *      ICANON  : canonical mode (not reading byte-by-byte)
     *      IEXTEN  : ^V
     *      ISIG    : signals like SIGINT (on ^C) and SIGSTP (on ^Z)
     */
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    /* Set character size to 8 bits per byte.
     * This isn't always necessary */
    raw.c_cflag |= (CS8);

    /* Set timeout for read() */
    raw.c_cc[VMIN] = 0;     /* read() returns as soon as there's input */
    raw.c_cc[VTIME] = 1;    /* read() times out after 100 milliseconds */

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

static inline void disable_raw_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void prnt_scr(screen_t *ptr){
  *ptr = get_screen_size();
 MAX_COLS = ptr->cols;
 MAX_ROWS = ptr->lines;
  printws(NULL, "MAX_COL = %d; MAX_ROW = %d", MAX_COLS, MAX_ROWS);
}

int touch_init(void){
  if((fd = open(I2C_DEV_FILE, O_RDWR)) < 0){
   printf("%s : Unable to open %s\n", __func__, I2C_DEV_FILE);
   return EXIT_FAILURE;

  }

  if(ioctl(fd, I2C_SLAVE, TOUCH_SLAVE_ADDR) < 0){
   printf("%s : Failed to setup %s\n", __func__, "Touch Sensor");
   return EXIT_FAILURE;
    
  }

  printf("%d\n", fd);
  return 0;
  
}

/*read "len" many bytes from "addr" of the sensor in to the adresss indicated by "pBuffer" */
int touch_read(uint8_t base_addr, int *pBuffer)
{
  int ret;
  char buf[2];
  buf[0]=base_addr;
  ret = write(fd,buf,1);
  if (ret <= 0)
  {
      perror("write address failed\n");
      return 1;
  }

  ret = read(fd,pBuffer,1);
  if(ret <= 0)
  {
      perror("read failed\n");
      return 1;
  }
  return 0;
}

int main(int argc, char *argv[]){
  if(touch_init())
    return EXIT_FAILURE;
  enable_raw_mode();
  screen_t screen_size;
  prnt_scr(&screen_size);
  point_t cur_cursor;
  clear_screen(); 
  int prev_val = 0;
  char c;
  printws(NULL, "\033[?25l");


  style_t test_style[] = {
      /*   fg            bg             mode       */
      { BLUE_FG,    YELLOW_BG,       BLINKING}, /* [0] */
      { BLUE_FG,    RED_BG,       BOLD}       /* [1] */
  };


   /* Prepare some demo shape */
  box_t shape[] = {
      {   /* [0] */
          RECTANGLE,                      /*                     type */
          { 0, 12 },                     /*                   origin */
          test_style[0], test_style[1],   /*     border & fill styles */
          12, 13,                         /*           width & height */
          '#', '/',                       /* border & fill characters */
  }};

  draw(&shape[0]);

  while(1){
    if(touch_read(BIG_BUTTON, &buf[0]) || touch_read(SLIDER, &buf[1])){
      perror("Read failed\n");
      return EXIT_FAILURE;

    }

    erase(&shape[0]);
    switch(buf[0]){
      case 1 : 
               shape[0].border.bg++;
               if(shape[0].border.bg > DEFAULT_BG)
                shape[0].border.bg = BLACK_BG;
               break;

      case 2 : 
               shape[0].fill.bg++;
               if(shape[0].fill.bg > DEFAULT_BG)
                shape[0].fill.bg = BLACK_BG;
               break;

      case 3 :
               cur_cursor = get_cursor_pos();
               shape[0].origin.x = 0;
               shape[0].origin.y = 12;
               break;

    }

    if(buf[1] > 0){
      nudge(&shape[0], RIGHT, buf[1]/10);
      prev_val = buf[1];

    }

    draw(&shape[0]);
    buf[0] = 0;
    read(STDIN_FILENO, &c, 1);
    if(c == 'q')
     break;
    usleep(20 * 1000);

  }

  clear_screen();
  disable_raw_mode();
  
  return 0;
}

