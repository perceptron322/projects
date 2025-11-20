#include "../include/myTerm.h"

// производит очистку и перемещение курсора в левый верхний угол экрана
int
mt_clrscr ()
{
  printf ("\033[H\033[2J");
  return 0;
}