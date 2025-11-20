#include "../include/mySimpleComputer.h"
#include "sc_variables.h"

void
printDecodedCommand (int value)
{
  int sign, command, operand;
  sc_commandDecode (value, &sign, &command, &operand);
  printf ("%c%02X%02X", (sign ? '-' : '+'), command, operand);
}