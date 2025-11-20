#include "../include/mySimpleComputer.h"
#include "sc_variables.h"

void
printAccumulator (void)
{
  int val = 0;
  sc_accumulatorGet (&val);

  printf ("sc: ");
  printDecodedCommand (val);
  printf (" hex: %04X", (unsigned int)val & 0xffff);
}
