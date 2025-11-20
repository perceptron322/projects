#include "../include/myBigChars.h"

int
bc_strlen (char *str)
{
  if (str == NULL)
    return 0;

  int len = 0;
  for (; *str; ++str)
    if ((*str & 0xC0) != 0x80)
      ++len;
  return len;
}