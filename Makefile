# CFLAGS=-Wall -Wextra -Isrc/ -lpthread # Re-enable to add all warnings
CFLAGS=-Isrc/ -Ishare/ -lpthread
CC = gcc

TARGET_OUT=target
TARGET_FILES=./cmd/main.c

SRC_FILES = $(wildcard ./src/**/*.c ./src/*.c)
SRC_OBJS= $(SRC_FILES:.c=.o)

TARGET_CFLAGS=

all: target

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Targets 
target: ${TARGET_FILES} $(SRC_OBJS)
	$(CC) ${CFLAGS} $(TARGET_CFLAGS) -o${TARGET_OUT} $(SRC_OBJS) ${TARGET_FILES}

clean:
	rm -f $(TARGET_OUT)
	rm -f $(SRC_OBJS)
