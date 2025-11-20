#include "../include/myBigChars.h"

int
bc_bigcharwrite (FILE *file, int *big, int count)
{
  if (file == NULL)
    return -1;
  fwrite (big, sizeof (int), count * 2, file);
  return 0;
}