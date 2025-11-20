#include "../include/mySimpleComputer.h"
#include "sc_variables.h"
#include <stdlib.h>

void
printCounters (void)
{
  int val = 0;
  sc_icounterGet (&val);
  printf ("IC: %c%04X", (val >= 0 ? '+' : '-'), abs (val));
}