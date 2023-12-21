CC = gcc
CFLAGS = -Wall -Werror
RM = rm -rf
INC_DIR = /usr/local/include
LIB_DIR = /usr/local/lib
LIBS = -lraylib -lm

.PHONY: clean

scb: src/scb.c
	$(CC) $(CFLAGS) $^ -o $@ -I$(INC_DIR) -L$(LIB_DIR) $(LIBS)

clean:
	$(RM) scb
