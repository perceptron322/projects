#include "../include/myTerm.h"

int
mt_gotoXY (int x, int y)
{
  int rowsMax = 0, colsMax = 0;

  mt_getscreensize (&rowsMax, &colsMax);

  if ((y + 1 > 0) && (x + 1 > 0) && (y + 1 <= rowsMax) && (x + 1 <= colsMax))
    {
      printf ("\033[%d;%dH", y + 1, x + 1);
      return 0;
    }

  return -1;
}