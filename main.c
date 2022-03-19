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

/* This is the I2C slave address of TOUCH sensor */                                                                                                                                                          
#define TOUCH_SLAVE_ADDR 0x08

int main(int argc, char *argv[]){
  
  return 0;
}
