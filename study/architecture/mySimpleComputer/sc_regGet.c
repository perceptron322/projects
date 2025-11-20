#include "../include/mySimpleComputer.h"
#include "sc_variables.h"
#include <stdlib.h>

int
sc_regGet (int reg, int *value)
{
  if (reg < 0 || reg >= 5)
    return -1;

  if (value == NULL)
    return -1;

  *value = (flagRegister >> reg) & 0x1;
  *value = ((flagRegister & reg) == 0) ? 0 : 1;
  return 0;
}