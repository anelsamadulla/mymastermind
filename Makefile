#my_mastermind.o: my_mastermind.c
#	gcc -g -o my_mastermind my_mastermind.c

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror -o0 -std=c99

LDFLAGS = -lm

SOURCES = my_mastermind.c 
OBJECTS = $(SOURCES:.c=.o)
TARGET = my_mastermind

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	@rm -f $(TARGET) $(OBJECTS) core
