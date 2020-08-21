CFLAGS = -g -std=c99 -Wall -Werror

coder: coder.o confab.o
	gcc coder.o confab.o -lm -o coder

coder.o: coder.c confab.h
	gcc $(CFLAGS) -c coder.c

confab.o: confab.c
	gcc $(CFLAGS) -lm -c confab.c 

clean:
	rm *.o
