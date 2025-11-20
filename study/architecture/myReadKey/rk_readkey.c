#include "myReadKey.h"
#include "rk_variables.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
rk_readKey (enum Keys *key)
{
  char *keypair[]
      = { "0",     "1",        "2",        "3",      "4",      "5",
          "6",     "7",        "8",        "9",      "a",      "b",
          "c",     "d",        "e",        "f",      "-",      "+",
          "l",     "s",        "i",        "r",      "t",      "\n",
          "\033",  "\033[15~", "\033[17~", "\033[A", "\033[B", "\033[D",
          "\033[C" };

  rk_mytermsave ();

  char buf[6] = { 0 };
  rk_mytermregime (1, 0, 1, 1, 1);

  read (STDIN_FILENO, buf, 6);

  for (int i = 0; i < 31; i++)
    if (strcmp (buf, keypair[i]) == 0)
      {

        *key = i;
        break;
      }

  rk_mytermrestore ();

  return 0;
}