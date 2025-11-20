#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITS 15

void
logg (const char *message)
{
  FILE *file = fopen ("log.txt", "a"); // Открываем файл для добавления
  if (file == NULL)
    {
      perror ("Ошибка открытия файла");
      return;
    }

  fprintf (file, "%s\n", message); // Пишем сообщение
  fclose (file);                   // Закрываем файл
}

char *
binstr (int num)
{
  static char binary_str[BITS + 1 + 8]; // Enough space for binary + " (0xXX)"
  char hex_part[8];                     // Now safely fits " (0xXX)\0"

  // Generate binary string
  for (int i = 0; i < BITS; i++)
    {
      binary_str[BITS - 1 - i] = (num & (1 << i)) ? '1' : '0';
    }
  binary_str[BITS] = '\0';

  // Generate hex part (2 digits, e.g., " (0x0F)")
  snprintf (hex_part, sizeof (hex_part), " (0x%02X)", num & 0xFF);

  // Concatenate
  strcat (binary_str, hex_part);

  return binary_str;
}