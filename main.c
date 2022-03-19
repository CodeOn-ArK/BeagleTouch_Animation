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

int fd;

int main(int argc, char *argv[]){
  
  return 0;
}


/*read "len" many bytes from "addr" of the sensor in to the adresss indicated by "pBuffer" */
int touch_read(uint8_t base_addr, char *pBuffer,uint32_t len)
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

  ret = read(fd,pBuffer,len);
  if(ret <= 0)
  {
      perror("read failed\n");
  }
  return 0;
}

