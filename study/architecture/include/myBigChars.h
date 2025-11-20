#pragma once

#include "myTerm.h"

#define LTCORNER "┌"
#define LBCORNER "└"
#define RTCORNER "┐"
#define RBCORNER "┘"

#define HORIZONTAL "─"
#define VERTICAL "│"
#define CHARFILL "▓"

int bc_strlen (char *str);

int bc_printA (char *str);
int bc_box (int y, int x, int width, int height, enum colors box_fg,
            enum colors box_bg, char *header, enum colors header_fg,
            enum colors header_bg);

int bc_setbigcharpos (int *big, int x, int y, int value);
int bc_getbigcharpos (int big, int x, int y, int *value);

int bc_printbigchar (int letter[2], int x, int y, enum colors fg,
                     enum colors bg);

int bc_bigcharwrite (FILE *file, int *big, int count);
int bc_bigcharread (FILE *fd, int *big, int count);