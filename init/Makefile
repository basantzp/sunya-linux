CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c99
TARGET = init
SRC = init.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)

install: $(TARGET)
	cp $(TARGET) /sbin/

.PHONY: all clean install
