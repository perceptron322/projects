#include "../include/console.h"

int
getNormalInt (int memoryInt)
{
  int sign = (memoryInt >> 14) & 0x1;
  int value = memoryInt & 0x7fff;
  if (sign == 1)
    value = -value;
  return value;
}

int
getMemoryInt (int normal)
{
  int sign = (normal < 0);
  int value = normal;
  if (sign == 1)
    value = -value;

  value = value & 0x7fff;
  value = value | (sign << 14);
  return value;
}

bool
checkMemoryRange (int value)
{
  if (value > 16383 || value < -16383)
    return false;
  return true;
}