# Компилятор
CC = gcc

# Пути к заголовочным файлам
INCLUDE_DIRS = -I../include -I../mySimpleComputer -I../myTerm

# Пути к библиотекам
LIB_PATHS = -L../mySimpleComputer -L../myTerm

# Имена библиотек (без префикса 'lib' и расширения '.a')
LIBS = -l_mySimpleComputer -l_myTerm

# Флаги компиляции
CFLAGS = -Wall -Wextra $(INCLUDE_DIRS)
LDFLAGS = $(LIB_PATHS) $(LIBS)

# Имя исполняемого файла
TARGET = sat

# Файлы по умолчанию
INPUT_FILE = input.txt
OUTPUT_FILE = ../output.bin

.PHONY: all clean run

all: $(TARGET)

$(TARGET): sat.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET) $(INPUT_FILE) $(OUTPUT_FILE)

clean:
	rm -f $(TARGET) $(OUTPUT_FILE)