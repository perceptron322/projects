#include "../include/myReadKey.h"
#include "rk_variables.h"

int
rk_mytermsave ()
{
  tcgetattr (STDIN_FILENO, &tty);
  savetty = tty;
  return 0;
}