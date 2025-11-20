#include "../include/myTerm.h"

int
mt_setcursorvisible (bool value)
{
  if (!value)
    {
      printf ("\033[?25l");
    }
  else
    {
      printf ("\033[?12l\033[?25h");
    }
  return 0;
}
