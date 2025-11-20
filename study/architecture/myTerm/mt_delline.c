#include "../include/myTerm.h"

// очищает текущую строку
int
mt_delline (void)
{
  if (write (STDOUT_FILENO, "\033[K", 3) != 3)
    return -1;
  return 0;
}