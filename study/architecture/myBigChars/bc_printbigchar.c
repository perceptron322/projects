#include "../include/myBigChars.h"

int
bc_printbigchar (int letter[2], int x, int y, enum colors fg, enum colors bg)
{
  mt_setfgcolor (fg);
  mt_setbgcolor (bg);
  for (int i = 0; i < 64; i++)
    {
      mt_gotoXY (x + (i % 8), y + (i / 8));
      char *temp = ((letter[i >= 32] >> (i % 32)) & 1) ? CHARFILL : " ";
      printf ("%s%s", temp, ((i % 7) ? "" : "\n"));
    }
  // mt_setdefaultcolor ();
  return 0;
}