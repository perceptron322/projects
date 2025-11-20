#include "../include/myBigChars.h"

int
bc_bigcharread (FILE *file, int *big, int count)
{
  if (file == NULL)
    return -1;

  return fread (big, sizeof (int), count * 2, file);
}