/*============================================================================
 Name        : main.c
 Author      : ArK (1930038@kiit.ac.in)
 Version     : v1.0
 Copyright   : Your copyright notice
 Description : 
 ============================================================================*/


#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

#include <ctype.h>
#include <termios.h>
#include <unistd.h>

//#include <io.h>
#include "ansi/cursor.h"
#include "ansi/screen.h"
#include "ansi/colors.h"
#include "graphics/common.h"
#include "graphics/box.h"

/* This is the I2C slave address of TOUCH sensor */                                                                                                                                                          
#define TOUCH_SLAVE_ADDR 0x08

#define I2C_DEV_FILE    "/dev/i2c-2"
#define BIG_BUTTON      0x00
#define SLIDER          0x01

int fd;
int touch_init(void);
int touch_read(uint8_t base_addr, int *pBuffer);
int buf[2] = {0};

struct termios orig_termios;    /* Keeps the original attributes */

static inline void enable_raw_mode(void);
static inline void disable_raw_mode(void);

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


int main(int argc, char *argv[]){
  if(touch_init())
    return EXIT_FAILURE;

  int prev_val = 0;
  while(1){
    if(touch_read(BIG_BUTTON, &buf[0]) && touch_read(SLIDER, &buf[1])){
      perror("Read failed\n");
      return EXIT_FAILURE;
    }
    usleep(50 * 1000);

    enable_raw_mode();

    switch(buf[0]){
//      case 0 : printf("-\n") ;
//               break;
      case 1 : printf("|\n");
               break;
      case 2 : printf("+\n");
               break;
    }

    if(buf[1] < prev_val){
      printf("2\n") ;
    }

    prev_val = buf[1];
    buf[0] = 0;

  }

  disable_raw_mode();
  
  return 0;
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
      return -1;
  }

  ret = read(fd,pBuffer,1);
  if(ret <= 0)
  {
      perror("read failed\n");
  }
  return 0;
}

