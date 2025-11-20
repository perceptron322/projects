#include "../include/mySimpleComputer.h"
#include "sc_variables.h"
#include <stdlib.h>

int
sc_commandValidate (int command)
{
  if (command != C_LOAD && command != C_WRITE && command != C_STORE
      && command != C_READ && command != C_ADD && command != C_SUB
      && command != C_DIVIDE && command != C_MUL && command != C_JZ
      && command != C_JNEG && command != C_HALT && command != C_JUMP
      && command != C_ASSIGN1 && command != C_LOGLC && command != C_LOGRC)
    return -1;

  return 0;
}