CC = gcc
CFLAGS = -Wall -Wextra -I. -I../include -fPIC
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
LIB = lib_myTerm.a

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(LIB)