#include "../include/myBigChars.h"
#include <stdlib.h>

void
string_decode (int *letter, char *str)
{
  for (int i = 0; i < 8 * 6; i++)
    {
      // printf ("%d : %d - %c    ", ((i % 6) + 1), (i / 6), (str[i]));
      bc_setbigcharpos (letter, (i % 6) + 1, i / 6, (str[i] == '#') ? 1 : 0);
    }
}

void
letter_0 (int *letter)
{
  char str[] = "#######    ##    ##    ##    ##    ##    #######";
  string_decode (letter, str);
}

void
letter_1 (int *letter)
{
  char str[] = "    ##  ######  ##    ##    ##    ##    ##    ##";
  string_decode (letter, str);
}
void
letter_2 (int *letter)
{
  char str[] = "######     #     ########     #     #     ######";
  string_decode (letter, str);
}
void
letter_3 (int *letter)
{
  char str[] = "######     #     #######     #     #     #######";
  string_decode (letter, str);
}
void
letter_4 (int *letter)
{
  char str[] = "##  ####  ####  ########    ##    ##    ##    ##";
  string_decode (letter, str);
}
void
letter_5 (int *letter)
{
  char str[] = "#######     #     ######     #     #     #######";
  string_decode (letter, str);
}
void
letter_6 (int *letter)
{
  char str[] = "#######     #     #######    ##    ##    #######";
  string_decode (letter, str);
}
void
letter_7 (int *letter)
{
  char str[] = "######    ##    ##   ##   ##   ##   ##    ##    ";
  string_decode (letter, str);
}
void
letter_8 (int *letter)
{
  char str[] = "#######    ##    ########    ##    ##    #######";
  string_decode (letter, str);
}
void
letter_9 (int *letter)
{
  char str[] = "#######    ##    #######     #     #     #######";
  string_decode (letter, str);
}
void
letter_a (int *letter)
{
  char str[] = "  ##   #  # #    ##    ########    ##    ##    #";
  string_decode (letter, str);
}

void
letter_b (int *letter)
{
  char str[] = "##### #    ##    ###### #    ##    ##    ###### ";
  string_decode (letter, str);
}
void
letter_c (int *letter)
{
  char str[] = "#######    ##     #     #     #     #    #######";
  string_decode (letter, str);
}
void
letter_d (int *letter)
{
  char str[] = "##### #   ###    ##    ##    ##    ##   ####### ";
  string_decode (letter, str);
}
void
letter_e (int *letter)
{
  char str[] = "#######     #     #######     #     #     ######";
  string_decode (letter, str);
}
void
letter_f (int *letter)
{
  char str[] = "#######     #     #######     #     #     #     ";
  string_decode (letter, str);
}

void
letter_plus (int *letter)
{
  char str[] = "              ##   ####  ####   ##              ";
  string_decode (letter, str);
}

void
letter_minus (int *letter)
{
  char str[] = "                  ############                  ";
  string_decode (letter, str);
}

void
fillDecodedLetters (int *letters)
{
  letter_0 (letters);
  letter_1 (&letters[2]);
  letter_2 (&letters[4]);
  letter_3 (&letters[6]);
  letter_4 (&letters[8]);
  letter_5 (&letters[10]);
  letter_6 (&letters[12]);
  letter_7 (&letters[14]);
  letter_8 (&letters[16]);
  letter_9 (&letters[18]);

  letter_a (&letters[20]);
  letter_b (&letters[22]);
  letter_c (&letters[24]);
  letter_d (&letters[26]);
  letter_e (&letters[28]);
  letter_f (&letters[30]);

  letter_plus (&letters[32]);
  letter_minus (&letters[34]);
}

int
main ()
{
  char *path = "font.bin";
  FILE *file = fopen (path, "w+b");

  int *letters = (int *)malloc (36 * sizeof (int));
  fillDecodedLetters (letters);
  bc_bigcharwrite (file, letters, 18);

  free (letters);
  fclose (file);
}