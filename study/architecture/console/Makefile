# CC = gcc
# CFLAGS = -Wall -Wextra -I../include
# LDFLAGS = -L../mySimpleComputer -L../myTerm -L../myBigChars -L../myReadKey -L../ -no-pie
# LIBS = -l_mySimpleComputer -l_myTerm -l_myBigChars -l_myReadKey

# SRC = main.c
# OBJ = $(SRC:.c=.o)
# TARGET = main.exe

# .PHONY: all clean

# all: $(TARGET)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# pr03.o: pr03.c ../include/myBigChars.h ../include/myTerm.h ../include/mySimpleComputer.h ../include/myReadKey.h


# $(TARGET): $(OBJ)
# 	$(CC) $(OBJ) $(LDFLAGS) $(LIBS) -o $@

# clean:
# 	rm -f $(TARGET) $(OBJ)

CC = gcc
CFLAGS = -Wall -Wextra -I ../include -fPIC -std=gnu11 -D_FORTIFY_SOURCE=0
LDFLAGS = -no-pie



SRC = $(filter-out font.c, $(wildcard *.c))
OBJ = $(SRC:.c=.o)
LIB := $(shell find ../ -type f -name "*.a")
TARGET = main.exe

.PHONY: all clean

all: $(TARGET) font.exe

$(TARGET) : $(OBJ) $(LIB) ui_variables.c ui_variables.h
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

font.exe: font.c
	$(CC) $(CFLAGS) font.c -o font.exe $(LIB)

clean:
	rm -f *.exe *.o
