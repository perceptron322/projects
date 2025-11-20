#include "../include/myTerm.h"

int
mt_setfgcolor (enum colors color)
{
  switch (color)
    {
    case BLACK:
      printf ("\033[38;5;0m");
      return 0;
    case RED:
      printf ("\033[38;5;1m");
      return 0;
    case GREEN:
      printf ("\033[38;5;2m");
      return 0;
    case YELLOW:
      printf ("\033[38;5;3m");
      return 0;
    case BLUE:
      printf ("\033[38;5;4m");
      return 0;
    case MAGENTA:
      printf ("\033[38;5;5m");
      return 0;
    case CYAN:
      printf ("\033[38;5;6m");
      return 0;
    case WHITE:
      printf ("\033[38;5;7m");
      return 0;
    default:
      return -1;
    }
}