CC = g++
CFLAGS=-g -Wall -std=c++20
TARGET = bin/quick_sort
SRCS=main.cpp

$(TARGET): $(SRCS)
	mkdir -p bin
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)