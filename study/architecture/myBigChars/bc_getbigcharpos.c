#include "../include/myBigChars.h"

int
bc_getbigcharpos (int big, int x, int y, int *value)
{
  *value = (big << ((x - 1) + (y - 1) * 8)) & 1;
  return 0;
}