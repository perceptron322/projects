#include "../include/console.h"

void
ui_accum (int x, int y)
{
  if (!boxDrawed)
    bc_box (x, y, 23, 3, WHITE, BLACK, "Аккумулятор", BLACK, GREEN);
  mt_gotoXY (x + 2, y + 1);
  if (editStatus == st_Accumulator)
    mt_setfgcolor (GREEN);
  printAccumulator ();
  mt_setdefaultcolor ();
}