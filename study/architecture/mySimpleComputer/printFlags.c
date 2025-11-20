#include "../include/mySimpleComputer.h"
#include "sc_variables.h"

void
printFlags (void)
{
  char flag[] = "P0MTE";
  int temp = flagRegister;

  int j = 16;
  for (int i = 0; i < 5; i++)
    {
      if (j <= temp)
        {
          temp -= j;
          printf ("%c", flag[i]);
        }
      else
        {
          printf ("%c", '_');
        }
      if (i != 4)
        printf ("  ");
      j /= 2;
    }
}