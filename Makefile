CC = gcc
CFLAGS = -Iinclude -Wall -g
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
OUT = thegraveyardshift

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT) -lraylib -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(OUT)
