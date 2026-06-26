CC	= gcc
CFLAGS	= -Wall -Wextra -O2 -g

wave2d: main.c
	$(CC) $(CFLAGS) -o wave2d main.c

wave1d: wave1d.c
	$(CC) $(CFLAGS) -o wave1d wave1d.c -lm 

clean:
	rm -f wave2d wave 1d
