CC = gcc
CFLAGS = -Wall -Werror
RM = rm -rf
INC_DIR = /usr/local/include
LIB_DIR = /usr/local/lib
LIBS = -lraylib -lm

.PHONY: clean

scb: src/scb.c bin/pgn.o bin/piece.o bin/draw.o | bin
	$(CC) $(CFLAGS) $^ -o $@ -I$(INC_DIR) -L$(LIB_DIR) $(LIBS)

bin/piece.o: src/piece.c src/piece.h | bin
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR) -L$(LIB_DIR)

bin/draw.o: src/draw.c src/draw.h src/piece.h | bin
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR) -L$(LIB_DIR)

bin/pgn.o: src/pgn.c src/pgn.h | bin
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR) -L$(LIB_DIR)

bin:
	mkdir bin

clean:
	$(RM) scb bin
