#include "../include/console.h"

void
startEdit (enum EditStatus status)
{
  editStatus = status;
  enum Keys key;
  updateInterface ();

  int sign = 0, command = 0, operand = 0;
  int saved;

  // save state
  switch (editStatus)
    {
    case st_Memory:
      sc_memoryGet (cursor_pos, &saved);
      sc_memorySet (cursor_pos, 0);
      break;
    case st_Accumulator:
      sc_accumulatorGet (&saved);
      sc_accumulatorSet (0);
      break;
    case st_Counter:
      sc_icounterGet (&saved);
      sc_icounterSet (0);
      break;
    case st_None:
      return;
    }

  // считывание знака
  while (true)
    {
      rk_readKey (&key);
      if (key == KEY_PLUS || key == KEY_MINUS)
        {
          sign = (key % 2 == 0);
          int temp;
          sc_commandEncode (sign, command, operand, &temp);

          switch (editStatus)
            {
            case st_Memory:
              sc_memorySet (cursor_pos, temp);
              break;
            case st_Accumulator:
              sc_accumulatorSet (temp);
              break;
            case st_Counter:
              sc_icounterSet (temp);
              break;
            case st_None:
              return;
            }

          break;
        }
      else if (key == KEY_ESC)
        {
          switch (editStatus)
            {
            case st_Memory:
              sc_memorySet (cursor_pos, saved);
              break;
            case st_Accumulator:
              sc_accumulatorSet (saved);
              break;
            case st_Counter:
              sc_icounterSet (saved);
              break;
            case st_None:
              return;
            }
          editStatus = st_None;
          return;
        }
    }
  updateInterface ();

  int temp[4] = { 0, 0, 0, 0 };
  for (int i = 0; i < 4; i++)
    {

      while (true)
        {
          rk_readKey (&key);
          if (key == KEY_ESC || key == KEY_ENTER)
            {
              if (key == KEY_ESC)
                {
                  switch (editStatus)
                    {
                    case st_Memory:
                      sc_memorySet (cursor_pos, saved);
                      break;
                    case st_Accumulator:
                      sc_accumulatorSet (saved);
                      break;
                    case st_Counter:
                      sc_icounterSet (saved);
                      break;
                    case st_None:
                      return;
                    }
                }
              editStatus = st_None;
              return;
            }
          else if (key >= 16)
            continue;
          else if (i % 2 == 0 && key > 7)
            continue;

          temp[i] = key;
          command = temp[1] | (temp[0] << 4);
          operand = temp[3] | (temp[2] << 4);

          int value;
          sc_commandEncode (sign, command, operand, &value);
          switch (editStatus)
            {
            case st_Memory:
              sc_memorySet (cursor_pos, value);
              break;
            case st_Accumulator:
              sc_accumulatorSet (value);
              break;
            case st_Counter:
              sc_icounterSet (value);
              break;
            case st_None:
              return;
            }
          break;
        }

      updateInterface ();
    }
  editStatus = st_None;
  updateInterface ();
}