CC = gcc
CFLAGS=-g -Wall
TARGET = bin/quick_sort
SRCS=main.c

$(TARGET): $(SRCS)
	mkdir -p bin
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)