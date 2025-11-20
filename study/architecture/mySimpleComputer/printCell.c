#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"
#include "sc_variables.h"
#include <stdlib.h>

void
printCell (int address, enum colors fg, enum colors bg)
{
  mt_setfgcolor (fg);
  mt_setbgcolor (bg);

  int val = 0;
  sc_memoryGet (address, &val);
  int sign, command, operand;
  sc_commandDecode (val, &sign, &command, &operand);

  printf ("%c%02X%02X", (sign ? '-' : '+'), command, operand);
}