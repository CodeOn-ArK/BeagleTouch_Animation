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


[![demo](https://asciinema.org/a/486974.svg)](https://asciinema.org/a/486974)


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

## A bit about SYSCALLS 

This is a small intro taken from `Linux Manual pages`
```
NAME         top

       read - read from a file descriptor

SYNOPSIS         top

       #include <unistd.h>

       ssize_t read(int fd, void *buf, size_t count);

DESCRIPTION         top

       read() attempts to read up to count bytes from file descriptor fd
       into the buffer starting at buf.

       On files that support seeking, the read operation commences at
       the file offset, and the file offset is incremented by the number
       of bytes read.  If the file offset is at or past the end of file,
       no bytes are read, and read() returns zero.

       If count is zero, read() may detect the errors described below.
       In the absence of any errors, or if read() does not check for
       errors, a read() with a count of 0 returns zero and has no other
       effects.

       According to POSIX.1, if count is greater than SSIZE_MAX, the
       result is implementation-defined; see NOTES for the upper limit
       on Linux.
```
```
NAME         top

       write - write to a file descriptor

SYNOPSIS         top

       #include <unistd.h>

       ssize_t write(int fd, const void *buf, size_t count);

DESCRIPTION         top

       write() writes up to count bytes from the buffer starting at buf
       to the file referred to by the file descriptor fd.

       The number of bytes written may be less than count if, for
       example, there is insufficient space on the underlying physical
       medium, or the RLIMIT_FSIZE resource limit is encountered (see
       setrlimit(2)), or the call was interrupted by a signal handler
       after having written less than count bytes.  (See also pipe(7).)

       For a seekable file (i.e., one to which lseek(2) may be applied,
       for example, a regular file) writing takes place at the file
       offset, and the file offset is incremented by the number of bytes
       actually written.  If the file was open(2)ed with O_APPEND, the
       file offset is first set to the end of the file before writing.
       The adjustment of the file offset and the write operation are
       performed as an atomic step.

       POSIX requires that a read(2) that can be proved to occur after a
       write() has returned will return the new data.  Note that not all
       filesystems are POSIX conforming.

       According to POSIX.1, if count is greater than SSIZE_MAX, the
       result is implementation-defined; see NOTES for the upper limit
       on Linux.
```
```
NAME         top

       ioctl - control device

SYNOPSIS         top

       #include <sys/ioctl.h>

       int ioctl(int fd, unsigned long request, ...);

DESCRIPTION         top

       The ioctl() system call manipulates the underlying device
       parameters of special files.  In particular, many operating
       characteristics of character special files (e.g., terminals) may
       be controlled with ioctl() requests.  The argument fd must be an
       open file descriptor.

       The second argument is a device-dependent request code.  The
       third argument is an untyped pointer to memory.  It's
       traditionally char *argp (from the days before void * was valid
       C), and will be so named for this discussion.

       An ioctl() request has encoded in it whether the argument is an
       in parameter or out parameter, and the size of the argument argp
       in bytes.  Macros and defines used in specifying an ioctl()
       request are located in the file <sys/ioctl.h>.  See NOTES.
```
## About ansilib

Ansilib is a tiny lib meant for some neat and simple command-line based graphics. It can render rectangles, triangles and squares as of now.
The features of the shape can be independently modified to give different color/character for border area or fill area.
![Click here](https://github.com/CodeOn-ArK/ansi_anim) to know about the ANSI lib.


![plot](https://files.seeedstudio.com/wiki/Grove-Capacitive_Touch_Slide_Sensor-CY8C4014LQI/img/main.jpg)



![plot](https://files.seeedstudio.com/wiki/Grove-Capacitive_Touch_Slide_Sensor-CY8C4014LQI/img/pin_out_back.jpg)
