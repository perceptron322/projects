#include <ctype.h>
#include <mySimpleComputer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MEMORY_SIZE 128

typedef struct
{
  unsigned int operand : 7; // 7 бит под операнд
  unsigned int command : 7; // 7 бит под команду
  unsigned int sign : 1;    // 1 бит под знак
} MemoryCell;

void parse_line (const char *line, int *cell, char *cmd, char *arg,
                 char *comment);
int parseStrCommand (char *str);
int encodeCommand (int command, int operand, int *value);

int
main (int argc, char *argv[])
{
  if (argc < 3)
    {
      printf ("Usage: %s input.asm output.bin\n", argv[0]);
      return 1;
    }

  char *inputPath = argv[1];
  char *outputPath = argv[2];
  MemoryCell memory[MEMORY_SIZE] = { 0 };

  FILE *inputFile = fopen (inputPath, "r");
  if (!inputFile)
    {
      perror ("Failed to open input file");
      return 1;
    }

  char line[MAX_LINE_LENGTH];
  while (fgets (line, sizeof (line), inputFile))
    {
      // Пропускаем пустые строки и комментарии
      if (line[0] == '\n' || line[0] == ';')
        continue;

      // Удаляем перевод строки
      line[strcspn (line, "\n")] = '\0';

      // Парсим строку
      int cell = -1;
      char cmd[32] = { 0 };
      char arg[32] = { 0 };
      char comment[256] = { 0 };

      parse_line (line, &cell, cmd, arg, comment);

      // Пропускаем строки без команды
      if (cmd[0] == '\0')
        continue;

      // Преобразуем команду в код
      int command = parseStrCommand (cmd);
      if (command == -1)
        {
          printf ("Unknown command: %s\n", cmd);
          continue;
        }

      // Преобразуем аргумент в число
      int operand = 0;
      if (arg[0] != '\0')
        {
          operand = atoi (arg);
        }

      // Определяем знак
      int sign = (operand < 0) ? 1 : 0;
      operand = abs (operand);

      // Кодируем команду и операнд
      int value;
      if (!encodeCommand (command, operand, &value))
        {
          printf ("Error encoding command: %s %s\n", cmd, arg);
          continue;
        }

      // Если указана ячейка, используем ее, иначе последовательное размещение
      int targetCell = (cell != -1) ? cell : 0;
      if (targetCell >= 0 && targetCell < MEMORY_SIZE)
        {
          memory[targetCell].command = command;
          memory[targetCell].operand = operand;
          memory[targetCell].sign = sign;
        }
      else
        {
          printf ("Invalid cell number: %d\n", cell);
        }
    }
  fclose (inputFile);

  // Сохраняем в бинарный файл
  FILE *outputFile = fopen (outputPath, "wb");
  if (!outputFile)
    {
      perror ("Failed to open output file");
      return 1;
    }

  size_t written
      = fwrite (memory, sizeof (MemoryCell), MEMORY_SIZE, outputFile);
  fclose (outputFile);

  printf ("Successfully written %zu memory cells to %s\n", written,
          outputPath);
  return 0;
}

int
encodeCommand (int command, int operand, int *value)
{
  if (operand < 0 || operand > 127)
    {
      return 0; // Операнд должен быть в диапазоне 0-127
    }

  *value = (command << 7) | operand;
  return 1;
}

void
parse_line (const char *line, int *cell, char *cmd, char *arg, char *comment)
{
  *cell = -1;
  cmd[0] = '\0';
  arg[0] = '\0';
  comment[0] = '\0';

  while (isspace (*line))
    line++;

  if (sscanf (line, "%d", cell) != 1)
    {
      *cell = -1;
    }
  while (isdigit (*line))
    line++;
  while (isspace (*line))
    line++;

  sscanf (line, "%s", cmd);
  line += strlen (cmd);
  while (isspace (*line))
    line++;

  const char *semicolon = strchr (line, ';');
  if (semicolon)
    {
      strncpy (arg, line, semicolon - line);
      arg[semicolon - line] = '\0';
      for (int i = strlen (arg) - 1; i >= 0 && isspace (arg[i]); i--)
        {
          arg[i] = '\0';
        }
      strcpy (comment, semicolon + 1);
    }
  else
    {
      strcpy (arg, line);
    }
}

int
parseStrCommand (char *str)
{
  if (strcmp (str, "NOP") == 0)
    return C_NOP;
  else if (strcmp (str, "CPUINFO") == 0)
    return C_CPUINFO;
  else if (strcmp (str, "READ") == 0)
    return C_READ;
  else if (strcmp (str, "WRITE") == 0)
    return C_WRITE;
  else if (strcmp (str, "LOAD") == 0)
    return C_LOAD;
  else if (strcmp (str, "STORE") == 0)
    return C_STORE;
  else if (strcmp (str, "ADD") == 0)
    return C_ADD;
  else if (strcmp (str, "SUB") == 0)
    return C_SUB;
  else if (strcmp (str, "DIVIDE") == 0)
    return C_DIVIDE;
  else if (strcmp (str, "MUL") == 0)
    return C_MUL;
  else if (strcmp (str, "JUMP") == 0)
    return C_JUMP;
  else if (strcmp (str, "JNEG") == 0)
    return C_JNEG;
  else if (strcmp (str, "JZ") == 0)
    return C_JZ;
  else if (strcmp (str, "HALT") == 0)
    return C_HALT;
  else if (strcmp (str, "NOT") == 0)
    return C_NOT;
  else if (strcmp (str, "AND") == 0)
    return C_AND;
  else if (strcmp (str, "OR") == 0)
    return C_OR;
  else if (strcmp (str, "XOR") == 0)
    return C_XOR;
  else if (strcmp (str, "JNS") == 0)
    return C_JNS;
  else if (strcmp (str, "JC") == 0)
    return C_JC;
  else if (strcmp (str, "JNC") == 0)
    return C_JNC;
  else if (strcmp (str, "JP") == 0)
    return C_JP;
  else if (strcmp (str, "JNP") == 0)
    return C_JNP;
  else if (strcmp (str, "ASSIGN1") == 0)
    return C_ASSIGN1;
  else
    return -1; // Неизвестная команда
}