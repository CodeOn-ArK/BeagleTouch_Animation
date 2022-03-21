/*============================================================================
 Name        : main.c
 Author      : ArK (1930038@kiit.ac.in)
 Version     : v1.0
 Copyright   : 
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

#include <io.h>
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

int touch_init(void);
int touch_read(uint8_t base_addr, int *pBuffer);
static inline void enable_raw_mode(void);
static inline void disable_raw_mode(void);


