#include "../include/mySimpleComputer.h"
#include "sc_variables.h"

void
termInit ()
{
  for (int i = 0; i < 5; i++)
    {
      term_input[i] = -1;
    }
}