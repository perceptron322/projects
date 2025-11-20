#include "../include/myBigChars.h"

int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  if (x < 0 || x > 7 || y < 0 || y > 7 || (value != 1 && value != 0))
    return -1;

  int mask = (1 << (x + (y % 4) * 8));
  big[y > 3] = value ? (big[y > 3] | mask) : (big[y > 3] & ~mask);

  return 0;
}