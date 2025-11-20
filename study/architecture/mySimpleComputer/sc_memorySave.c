#include "../include/mySimpleComputer.h"
#include "sc_variables.h"
#include <stdlib.h>

int
sc_memorySave (char *filename)
{
  if (filename == NULL)
    return -1;

  FILE *file = fopen (filename, "wb");
  if (file == NULL)
    {
      return -1;
    }

  size_t bytes_written = fwrite (memory, sizeof (int), MEMORY_SIZE, file);

  if (bytes_written != (int)MEMORY_SIZE)
    {
      fclose (file);
      return -1;
    }

  fclose (file);

  return 0;
}