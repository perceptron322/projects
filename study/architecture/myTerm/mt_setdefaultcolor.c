#include "../include/myTerm.h"

int
mt_setdefaultcolor (void)
{
  mt_setfgcolor (WHITE);
  mt_setbgcolor (BLACK);
  // mt_setcursorvisible (true);
  return 0;
}