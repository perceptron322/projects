#include "../include/mySimpleComputer.h"
#include "sc_variables.h"

void
addTerm (int address, int input)
{
  for (int i = 0; i < 4; i++)
    {
      term_adress[i] = term_adress[i + 1];
      term_input[i] = term_input[i + 1];
      term_val[i] = term_val[i + 1];
    }

  term_adress[4] = address;
  term_input[4] = input;

  int val;
  // mk_get (address, &val);
  sc_memoryGet(address, &val);
  term_val[4] = val;
}