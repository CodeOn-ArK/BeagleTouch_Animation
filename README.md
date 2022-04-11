# BeagleTouch_Animation


A project involving interfacing `Capacacitive Touch sensor (CY8C401)` with the BeagleBone Green's I2C driver and controlling an user space application using the sensor created with `ANSI_ANIM` lib
The following tree explains the structure of the project :

```
            ❯ tree
            .
            ├── ansilib
            │   ├── inc
            │   │   ├── ansi
            │   │   │   ├── colors.h
            │   │   │   ├── common.h
            │   │   │   ├── cursor.h
            │   │   │   ├── screen.h
            │   │   │   └── style.h
            │   │   └── graphics
            │   │       ├── box.h
            │   │       ├── common.h
            │   │       └── shapes.h
            │   └── src
            │       ├── ansi
            │       │   ├── cursor.c
            │       │   ├── screen.c
            │       │   └── style.c
            │       └── graphics
            │           ├── box.c
            │           ├── common.c
            │           └── shapes.c
            ├── inc
            │   ├── io.h
            │   └── main.h
            ├── LICENSE
            ├── makefile
            ├── README.md
            └── src
                ├── io.c
                └── main.c

9 directories, 21 files
```


[![demo](https://asciinema.org/a/PX9BwMV06lbcqUCMdwdzBQbvE.svg)](https://asciinema.org/a/PX9BwMV06lbcqUCMdwdzBQbvE)


## `Linux System Programming` and the `project`

This project is a small effort to test out system programming in Linux using the widely available `BeagleBone Green` hardware.
It interfaces with a `capacitive touch panel` based on `cy8c401`  to read user data via the touch pads

- The program starts at `src/main.c` where it inits the I2C driver as well as setups up the sensor
- Once the sensor is setup, it conintously polls for values present at register values `0x01` and `0x02` of the sensor
- These registers of the sensor tell the present status of the touch pads
- A change in register `0x01` indicates that big buttons are pressed
- Otherwise a change in `0x02` indicates that the slider is being used.

The program polls the  register pair continuously and concurrently updates the ANSI graphics on the terminal
The buttons are used to change the border/fill colour while the slider is used to change the position of the shapes drawn on screen

The program starts at `main.c`, as usual, and then inits the required drivers as described.
It performs `IOCTL` syscall to setup I2C_DRIVER. It sends the I2C_SLAVE_ADDR signal along with the address of the I2C_SLAVE which is `0x08` in this case.
After setting up the driver for interacting with the slave, we can then read/write the registers of the SLAVE via `read()`/`write()` syscalls, which take the adress and/or the data to be written/read to/from the slave.

The resultant key combinations are then read from the sensor via `read()` syscall, which reads the data into a variable passed into the API. The value is then read which in turn is used to influence the graphics on terminal. This graphic element has been created using `ANSILIB` as mentioned next.

This demo illustrates the power of Linux System Calls using a project based on Linux System Programming.

## About ansilib

Ansilib is a tiny lib meant for some neat and simple command-line based graphics. It can render rectangles, triangles and squares as of now.
The features of the shape can be independently modified to give different color/character for border area or fill area.
![Click here](https://github.com/CodeOn-ArK/ansi_anim) to know about the ANSI lib.


![plot](https://files.seeedstudio.com/wiki/Grove-Capacitive_Touch_Slide_Sensor-CY8C4014LQI/img/main.jpg)



![plot](https://files.seeedstudio.com/wiki/Grove-Capacitive_Touch_Slide_Sensor-CY8C4014LQI/img/pin_out_back.jpg)
