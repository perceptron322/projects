#include "../include/console.h"

void
ui_memory (int x, int y)
{
  if (!boxDrawed)
    bc_box (x, y, 61, 15, WHITE, BLACK, "Оперативная память", BLACK, GREEN);
  int size = 10;
  int counter;
  sc_icounterGet (&counter);

  for (int i = 0; i < 128; i++)
    {
      mt_gotoXY ((i % size) * 6 + x + 1, (i / size) + y + 1);

      enum colors fg = WHITE;
      enum colors bg = BLACK;

      if (i == cursor_pos)
        {
          fg = BLACK;
          bg = WHITE;
        }
      if (i == counter)
        {
          fg = RED;
        }

      printCell (i, fg, bg);
    }
  mt_setdefaultcolor ();
}