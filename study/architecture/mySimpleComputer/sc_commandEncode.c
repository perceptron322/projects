#include "../include/mySimpleComputer.h"
#include "sc_variables.h"
#include <stdlib.h>

int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  if (sign != 0 && sign != 1)
    return -1;
  if (operand > 127)
    return -1;

  int val = 0;
  if (sign)
    val |= (1 << 14);
  val = val | (command << 7);
  val = val | operand;
  *value = val;

  return 0;
}