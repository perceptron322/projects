#include "../include/mySimpleComputer.h"
#include "sc_variables.h"
#include <stdlib.h>

int
sc_memorySet (int address, int value)
{

  if (address < 0 || address >= MEMORY_SIZE)
    return -1;

  // int MIN_MEMORY_VALUE = -(1 << 15);
  // int MAX_MEMORY_VALUE = (1 << 15) - 1;

  // if (value < MIN_MEMORY_VALUE || value > MAX_MEMORY_VALUE)
  //   {
  //     return -1;
  //   }

  memory[address] = value;

  return 0;
}

int
mk_Set (int address, int value)
{

  int MIN_MEMORY_VALUE = -(1 << 15);
  int MAX_MEMORY_VALUE = (1 << 15) - 1;

  if (value < MIN_MEMORY_VALUE || value > MAX_MEMORY_VALUE)
    {
      sc_regSet (FLAG_P, 1);
      return -1;
    }

  if (address < 0 || address > 127)
    {
      sc_regSet (FLAG_M, 1);
      return -1;
    }

  int casheRow = -1;
  for (int i = 0; i < 5; i++)
    if (casheNum[i] == address / 10)
      casheRow = i;

  if (casheRow == -1)
    {
      addToCashe (address / 10);
      casheRow = 4;
    }
  else
    {
      cashePrior (casheRow);
    }

  cashe[4][address % 10] = value;
  return 0;
}
