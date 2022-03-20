CC=gcc


all	: main.c
	$(CC) $^ -o Animate

run	:	
	./Animate

clean	: Animate
	rm -rf Animate
