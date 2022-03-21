CC=gcc
INC = -Iinc -Iansilib/inc
LDFLAGS = $(LIB)
CFLAGS = $(INC) 


SRCS = src/main.c \
       src/io.c \
       ansilib/src/ansi/screen.c \
       ansilib/src/ansi/cursor.c \
       ansilib/src/ansi/style.c \
       ansilib/src/graphics/common.c \
       ansilib/src/graphics/box.c \
       ansilib/src/graphics/shapes.c



OBJS = obj/main.o \
       obj/io.o \
       obj/ansi/screen.o \
       obj/ansi/cursor.o \
       obj/ansi/style.o \
       obj/graphics/common.o \
       obj/graphics/box.o \
       obj/graphics/shapes.o

.PHONY: all clean

all: bin/anim

bin/anim: $(OBJS)
	@mkdir -p bin
	$(CC) $(LDFLAGS) -o $@ $^

obj/graphics/%.o: ansilib/src/graphics/%.c
	@mkdir -p obj/graphics
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

obj/ansi/%.o: ansilib/src/ansi/%.c
	@mkdir -p obj/ansi
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

run	:	
	./Animate

clean	: 
	rm -rf bin obj
