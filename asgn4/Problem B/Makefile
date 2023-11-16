CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wno-unused-parameter
TARGET = growing_arrays
SOURCE = growing_arrays.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

