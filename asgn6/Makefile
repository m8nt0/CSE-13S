CC = gcc
CFLAGS = -Wall -Wextra -g

crawler: crawler.c curl.c pagedir.c url.c bag.c hashtable.c set.c
	$(CC) $(CFLAGS) -o crawler crawler.c curl.c pagedir.c url.c bag.c hashtable.c set.c -lcurl

.PHONY: clean

clean:
	rm -f crawler
