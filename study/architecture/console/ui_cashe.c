#include "../include/console.h"

void
ui_cashe (int x, int y)
{
  if (!boxDrawed)
    bc_box (x, y, 66, 7, WHITE, BLACK, "Кеш процессора", BLACK, GREEN);

  for (int i = 0; i < 5; i++)
    {
      mt_gotoXY (x + 1, y + 1 + i);
      printCasheLine (i);
    }
}