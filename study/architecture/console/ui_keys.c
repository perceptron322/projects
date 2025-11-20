#include "../include/console.h"

char stringInfo_matrix[5][10]
    = { "l - load", "s - save", "i - reset", "r - run", "t - step" };

char stringIngo_vertical[3][24]
    = { "ESC - выход", "F5 - accumulator", "F6 - instruction counter" };

void
ui_keys (int x, int y)
{
  if (!boxDrawed)
    bc_box (x, y, 31, 7, WHITE, BLACK, "Клавиши", BLACK, GREEN);

  for (int i = 0; i < 5; i++)
    {
      mt_gotoXY (POS_KEY_X + 1 + (i % 3) * 10, POS_KEY_Y + 1 + (i / 3));
      printf (stringInfo_matrix[i]);
    }

  for (int i = 0; i < 3; i++)
    {
      mt_gotoXY (POS_KEY_X + 1, POS_KEY_Y + 3 + i);
      printf (stringIngo_vertical[i]);
    }
}