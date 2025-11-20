#include "../include/myReadKey.h"
#include "rk_variables.h"

int
rk_mytermrestore ()
{
  if (tcsetattr (STDIN_FILENO, TCSANOW, &savetty))
    {
      return 1;
    }

  return 0;
}