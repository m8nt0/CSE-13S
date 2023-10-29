CC = gcc
CFLAGS = -Wall

coolness: coolness.c
	$(CC) $(CFLAGS) -o coolness coolness.c -lm

clean:
	rm -f coolness

