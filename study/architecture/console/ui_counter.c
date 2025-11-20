#include "../include/console.h"

void
ui_counter (int x, int y)
{
  if (!boxDrawed)
    bc_box (x, y, 23, 3, WHITE, BLACK, "Счетчик команд", BLACK, GREEN);
  mt_gotoXY (x + 3, y + 1);

  printf ("T: %02d    ", ticks);
  if (editStatus == st_Counter)
    mt_setfgcolor (YELLOW);
  printCounters ();
  mt_setdefaultcolor ();
}