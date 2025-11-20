#include "../include/console.h"

void
ui_flags (int x, int y)
{
  if (!boxDrawed)
    bc_box (x, y, 24, 3, WHITE, BLACK, "Регистр флагов", BLACK, GREEN);
  mt_gotoXY (x + 5, y + 1);
  printFlags ();
}