#include "../include/console.h"

void
ui_editCell (int x, int y)
{
  if (!boxDrawed)
    bc_box (x, y, 61, 3, WHITE, BLACK, "Редактируемая ячейка (формат)", BLACK,
            GREEN);
  mt_gotoXY (x + 1, y + 1);
  int value = 0;
  sc_memoryGet (cursor_pos, &value);

  int sign = (value >> 14) & 0x1;
  int parsed = value & 0x3fff;
  if (sign == 1)
    parsed = -parsed;
  printf ("dec: %05d | ", parsed);

  printf ("oct: ");

  if (((value >> 15) & 0x1) == 1)
    printf ("7");
  else
    printf ("0");

  for (int i = 5; i > 0; i--)
    {
      int temp = 0;
      temp += ((value >> (3 * i - 1)) & 0x1) * 4;
      temp += ((value >> (3 * i - 2)) & 0x1) * 2;
      temp += ((value >> (3 * i - 3)) & 0x1) * 1;
      printf ("%d", temp);
    }

  printf (" hex: %04X | ", (unsigned int)value & 0xffff);

  printf ("bin: ");
  for (int i = 14; i >= 0; i--)
    {
      printf ("%1d", (value >> i) & 0x1);
      if (i == 14 || i == 7)
        printf (" ");
    }
}