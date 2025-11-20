#include "../include/mySimpleComputer.h"
#include "sc_variables.h"
#include <stdlib.h>

int
sc_memoryLoad (char *filename)
{
  if (filename == NULL)
    return -1;

  FILE *file = fopen (filename, "rb");
  if (file == NULL)
    {
      return -1;
    }

  int backup_memory[MEMORY_SIZE];
  for (int i = 0; i < MEMORY_SIZE; i++)
    {
      backup_memory[i] = memory[i];
    }

  size_t bytes_read = fread (memory, sizeof (int), MEMORY_SIZE, file);
  if (bytes_read != (int)MEMORY_SIZE)
    {
      for (int i = 0; i < MEMORY_SIZE; i++)
        {
          memory[i] = backup_memory[i];
        }
      fclose (file);

      return -1;
    }

  fclose (file);

  return 0;
}