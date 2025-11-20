#include "../include/myBigChars.h"
#include <stdlib.h>

int
bc_box (int x, int y, int width, int height, enum colors box_fg,
        enum colors box_bg, char *header, enum colors header_fg,
        enum colors header_bg)
{

  int rows, cols;
  int h_len = bc_strlen (header) + 2;
  mt_getscreensize (&rows, &cols);
  if ((y + height - 1) > rows || (x + width - 1) > cols || h_len == 0
      || h_len > width)
    {
      return -1;
    }

  mt_setbgcolor (box_bg);
  mt_setfgcolor (box_fg);

  // corners
  mt_setfgcolor (GREEN);

  mt_gotoXY (x, y);
  bc_printA (LTCORNER);

  mt_gotoXY (x + width - 1, y);
  bc_printA (RTCORNER);

  mt_gotoXY (x, y + height - 1);
  bc_printA (LBCORNER);

  mt_gotoXY (x + width - 1, y + height - 1);
  bc_printA (RBCORNER);

  for (int i = 1; i < width - 1; i++)
    {
      mt_gotoXY (x + i, y);
      bc_printA (HORIZONTAL);
      mt_gotoXY (x + i, y + height - 1);
      bc_printA (HORIZONTAL);
    }

  for (int i = 1; i < height - 1; i++)
    {
      mt_gotoXY (x, y + i);
      bc_printA (VERTICAL);
      mt_gotoXY (x + width - 1, y + i);
      bc_printA (VERTICAL);
    }

  mt_setbgcolor (header_bg);
  mt_setfgcolor (header_fg);

  int h_med = h_len / 2 - 1;
  int b_med = width / 2 - 1;

  int h_padding = b_med - h_med;
  mt_gotoXY (x + h_padding, y);
  printf ("\033[1m %s ", header);

  if (h_len <= width - 4)
    {
      mt_setbgcolor (box_bg);
      mt_setfgcolor (box_fg);
      mt_gotoXY (x + h_padding - 1, y);
      mt_setfgcolor (GREEN);
      printf ("◀");
      mt_gotoXY (x + h_padding + h_len, y);
      printf ("▶");
      mt_setfgcolor (WHITE);
    }

  // mt_setdefaultcolor ();
  fflush (stdout);
  return 0;
}