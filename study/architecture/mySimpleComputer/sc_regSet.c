#include "../include/mySimpleComputer.h"
#include "sc_variables.h"
#include <stdlib.h>

int
sc_regSet (int reg, int value)
{
  if (reg != FLAG_0 && reg != FLAG_E && reg != FLAG_M && reg != FLAG_P
      && reg != FLAG_T)
    return -1;

  if (value != 0 && value != 1)
    return -1;

  if (value == 0)
    flagRegister &= ~(reg);
  else
    flagRegister |= reg;

  return 0;
}