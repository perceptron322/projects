#include "../include/console.h"

void
printNumberAsBig (int x, int y, int number, enum colors fg, enum colors bg)
{
  int sign, command, operand;
  sc_commandDecode (number, &sign, &command, &operand);
  bc_printbigchar (&big_chars[(sign == 1) ? 34 : 32], x, y, fg, bg);
  int hh[4];

  hh[0] = command / 16;
  hh[1] = command % 16;
  hh[2] = operand / 16;
  hh[3] = operand % 16;
  for (int i = 0; i < 4; i++)
    {
      bc_printbigchar (&big_chars[hh[i] * 2], x + 8 + i * 8, y, fg, bg);
    }
}

void
ui_big (int x, int y)
{
  if (!boxDrawed)
    bc_box (x, y, 47, 12, WHITE, BLACK, "Редактируемая ячейка (увеличено)",
            BLACK, GREEN);

  enum colors fontcolor;
  if (editStatus == st_Memory)
    fontcolor = YELLOW;
  else
    fontcolor = GREEN;

  int cell;
  sc_memoryGet (cursor_pos, &cell);
  printNumberAsBig (x + 3, y + 2, cell, fontcolor, BLACK);
}