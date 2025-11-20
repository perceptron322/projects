#include "../include/mySimpleComputer.h"
#include "sc_variables.h"
#include <stdlib.h>

int
sc_icounterGet (int *value)
{
  if (value == NULL)
    return -1;

  *value = commandCounter;

  return 0;
}