#include "../include/mySimpleComputer.h"
#include "sc_variables.h"

void
printTerm (int x, int y)
{
  for (int i = 0; i < 5; i++)
    {
      if (term_input[i] == -1)
        continue;
      mt_gotoXY (x, y + i);

      // int val;
      // mk_get (term_adress[i], &val);

      printf ("%02x%c ", term_adress[i], (term_input[i] == 1) ? '>' : '<');
      printDecodedCommand (term_val[i]);
    }
}