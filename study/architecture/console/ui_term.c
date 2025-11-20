#include "../include/console.h"

void
ui_term (int x, int y)
{
  if (!boxDrawed)
    bc_box (x, y, 11, 7, WHITE, BLACK, "IN--OUT", BLACK, GREEN);

  mt_setdefaultcolor ();
  printTerm (x + 1, y + 1);
}