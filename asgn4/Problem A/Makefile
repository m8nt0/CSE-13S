CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic

all: check_cycle

check_cycle: test_ll_cycle.c ll_cycle.c
	$(CC) $(CFLAGS) -Wno-sign-compare -o check_cycle test_ll_cycle.c ll_cycle.c

clean:
	rm -f check_cycle

