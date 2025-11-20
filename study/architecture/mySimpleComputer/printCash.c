#include "../include/mySimpleComputer.h"
#include "sc_variables.h"

// void
// printCasheLine (int line)
// {
//   int index = casheNum[line];
//   // if (index == 0x8000)
//   //   return;
//   // printf ("%02d: ", index);

//   for (int i = 0; i < 10; i++)
//     {
//       // some check
//       if (cashe[line][i] == 0x8000)
//         printf ("bebebe");
//       else
//       printDecodedCommand (cashe[line][i]);

//       printf (" ");
//     }
// }

void
printCasheLine (int line)
{
  int index = casheNum[line];

  if (index == 0x8000)
    {
      printf ("-1: ");
    }
  else
    {
      printf ("%02d: ", index);

      for (int i = 0; i < 10; i++)
        {
          printDecodedCommand (cashe[line][i]);
          printf (" ");
        }
    }
}