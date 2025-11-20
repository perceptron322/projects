#include "../include/console.h"

void
ui_command (int x, int y)
{
  if (!boxDrawed)
    bc_box (x, y, 24, 3, WHITE, BLACK, "Команда", BLACK, GREEN);
  mt_gotoXY (x + 6, y + 1);
  printCommand ();
}