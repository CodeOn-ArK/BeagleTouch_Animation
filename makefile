CC=gcc
INC = -Iinc -Iansilib/inc
CFLAGS = $(INC) 

all	: main.c
	$(CC) $(INC) $^ -o Animate

run	:	
	./Animate

clean	: Animate
	rm -rf Animate
