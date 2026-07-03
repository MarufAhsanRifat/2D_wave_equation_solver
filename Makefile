CC	= gcc
CFLAGS	= -Wall -Wextra -O2 -g -I ./src

# Step 3: grid test
grid_test: src/grid_test.o src/grid.o
	$(CC) $(CFLAGS) -o grid_test src/grid_test.o src/grid.o -lm

src/grid_test.o: src/grid_test.c src/grid.h
	$(CC) $(CFLAGS) -c -o src/grid_test.o src/grid_test.c

src/grid.o: src/grid.c src/grid.h
	$(CC) $(CFLAGS) -c -o src/grid.o src/grid.c

wave2d: main.c
	$(CC) $(CFLAGS) -o wave2d main.c

wave1d: wave1d.c
	$(CC) $(CFLAGS) -o wave1d wave1d.c -lm 

alloc_test: alloc_test.c
	$(CC) $(CFLAGS) -o alloc_test alloc_test.c -lm

clean:
	rm -f wave2d wave 1d grid_test src/*.o
