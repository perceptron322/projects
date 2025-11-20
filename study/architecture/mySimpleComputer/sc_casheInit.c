#include "../include/mySimpleComputer.h"
#include "sc_variables.h"

void
sc_casheInit ()
{
  for (int i = 0; i < 5; i++)
    {
      casheNum[i] = 0x8000;
      for (int j = 0; j < 10; j++)
        cashe[i][j] = 0x8000;
    }
}

void
addToCashe (int line)
{
  ticks += 10;
  if (casheNum[0] != 0x8000)
    {
      // for (int i = 0; i < ((casheNum[0] == 12) ? 8 : 10); i++)
      //   {
      //     sc_memorySet (casheNum[0] * 10 + i, cashe[0][i]);
      //   }
    }
  for (int i = 0; i < 4; i++)
    {
      casheNum[i] = casheNum[i + 1];
      for (int j = 0; j < 10; j++)
        {
          cashe[i][j] = cashe[i + 1][j];
        }
    }

  casheNum[4] = line;
  cashe[4][8] = 0x8000;
  cashe[4][9] = 0x8000;
  for (int i = 0; i < ((line == 12) ? 8 : 10); i++)
    {
      int val;
      sc_memoryGet (line * 10 + i, &val);
      cashe[4][i] = val;
    }
}

void
cashePrior (int index)
{
  int line = casheNum[index];

  int temp[10];
  for (int i = 0; i < 10; i++)
    {
      temp[i] = cashe[index][i];
    }

  for (int i = index; i < 4; i++)
    {
      for (int j = 0; j < 10; j++)
        cashe[i][j] = cashe[i + 1][j];
      casheNum[i] = casheNum[i + 1];
    }

  casheNum[4] = line;
  for (int i = 0; i < 10; i++)
    {
      cashe[4][i] = temp[i];
    }
}