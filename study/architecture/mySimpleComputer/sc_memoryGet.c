#include "../include/mySimpleComputer.h"
#include "sc_variables.h"
#include <stdlib.h>

int
sc_memoryGet (int address, int *value)
{

  if (address < 0 || address >= MEMORY_SIZE)
    return -1;

  if (value == NULL)
    {
      return -1;
    }

  *value = memory[address];

  return 0;
}

int
mk_get (int address, int *value)
{
  if (address < 0 || address >= MEMORY_SIZE)
    {
      sc_regSet (FLAG_M, 1);
      return -1;
    }

  int casheRow = -1;
  int check = 0;
  sc_memoryGet(address, &check);
  for (int i = 0; i < 5; i++)
    if ((casheNum[i] == address / 10))
    {
      if(cashe[i][address % 10] == check)
      {
        casheRow = i;
        ticks++;
      }
    }

  if (casheRow == -1)
    {
      addToCashe (address / 10);
      casheRow = 4;
    }
  else
    {
      cashePrior (casheRow);
    }

  *value = cashe[4][address % 10];
  return 0;
}