#pragma once

#include "myBigChars.h"
#include <string.h>
#include <termios.h>

typedef enum Keys
{
  KEY_0, // edit keys
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,
  KEY_A,
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_MINUS,
  KEY_PLUS,
  KEY_L, // functional keys
  KEY_S,
  KEY_I,
  KEY_R,
  KEY_T,
  KEY_ENTER,
  KEY_ESC,
  KEY_F5,
  KEY_F6,
  KEY_UP, // move keys
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT
} kkeys;

int rk_readKey (enum Keys *key);
int rk_mytermsave ();
int rk_mytermrestore ();
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
int rk_readvalue (int *value, int timeout);