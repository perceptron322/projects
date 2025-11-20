#include "../include/console.h"

void
ALU_add (int adr)
{
  int first;
  int second;
  sc_accumulatorGet (&first);

  if (mk_get (adr, &second) == -1)
    return;

  first = getNormalInt (first);
  second = getNormalInt (second);

  first += second;

  if (checkMemoryRange (first))
    {
      first = getMemoryInt (first);
      sc_accumulatorSet (first);
    }
  else
    {
      sc_regSet (FLAG_P, 1);
      return;
    }

  sc_icounterIncrement ();
}

void
ALU_mul (int adr)
{
  int first;
  int second;
  sc_accumulatorGet (&first);

  // sc_memoryGet (adr, &second);
  if (mk_get (adr, &second) == -1)
    return;

  first = getNormalInt (first);
  second = getNormalInt (second);

  first *= second;

  if (checkMemoryRange (first))
    {
      first = getMemoryInt (first);
      sc_accumulatorSet (first);
    }
  else
    {
      sc_regSet (FLAG_P, 1);
      return;
    }

  sc_icounterIncrement ();
}

void
ALU_div (int adr)
{
  int first;
  int second;
  sc_accumulatorGet (&first);

  if (mk_get (adr, &second) == -1)
    return;
  if (second == 0)
    {
      sc_regSet (FLAG_0, 1);
      return;
    }

  first = getNormalInt (first);
  second = getNormalInt (second);

  first /= second;

  if (checkMemoryRange (first))
    {
      first = getMemoryInt (first);
      sc_accumulatorSet (first);
    }
  else
    {
      sc_regSet (FLAG_P, 1);
      return;
    }

  sc_icounterIncrement ();
}

void
ALU_sub (int adr)
{
  int first;
  int second;
  sc_accumulatorGet (&first);

  if (mk_get (adr, &second) == -1)
    return;

  first = getNormalInt (first);
  second = getNormalInt (second);
  first -= second;

  if (checkMemoryRange (first))
    {
      first = getMemoryInt (first);
      sc_accumulatorSet (first);
    }
  else
    {
      sc_regSet (FLAG_P, 1);
      return;
    }

  sc_icounterIncrement ();
}

void
ALU (int command, int operand)
{
  switch (command)
    {
    case C_SUB:
      ALU_sub (operand);
      break;
    case C_DIVIDE:
      ALU_div (operand);
      break;
    case C_MUL:
      ALU_mul (operand);
      break;
    case C_ADD:
      ALU_add (operand);
      break;

    default:
      break;
    }
}