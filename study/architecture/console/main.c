#include "../include/console.h"
#include <stdlib.h>

void computerInit ();

void
switchIgnoring ()
{
  interactiveMode = !interactiveMode;

  if (interactiveMode)
    sc_regSet (FLAG_T, 0);
  else
    sc_regSet (FLAG_T, 1);
  updateInterface ();
}

void
moveCursor (int dir)
{
  if (dir < 0 || dir > 3)
    return;

  switch (dir)
    {

    case 0:
      if (cursor_pos >= 0 && cursor_pos < 10)
        {
          if (cursor_pos == 8 || cursor_pos == 9)
            {
              cursor_pos -= (20 - 130);
            }
          else
            {
              cursor_pos -= (10 - 130);
            }
        }
      else
        {
          cursor_pos -= 10;
        }
      break;

    case 1:
      if (cursor_pos % 10 == 9)
        {
          cursor_pos -= 9;
        }
      else if (cursor_pos == 127)
        {
          cursor_pos = 120;
        }
      else
        {
          cursor_pos++;
        }
      break;

    case 2:
      if (cursor_pos >= 120 && cursor_pos < 128)
        {
          cursor_pos += (10 - 130);
        }
      else if (cursor_pos == 119 || cursor_pos == 118)
        {
          cursor_pos += (20 - 130);
        }
      else
        {
          cursor_pos += 10;
        }
      break;
    case 3:
      if (cursor_pos % 10 == 0)
        {
          if (cursor_pos == 120)
            {
              cursor_pos = 127;
            }
          else
            {
              cursor_pos += 9;
            }
        }
      else
        {
          cursor_pos--;
        }
      break;
    }
}

void
readInput (char *message)
{
  mt_gotoXY (POS_MESSAGE_X, POS_MESSAGE_Y);
  printf ("%s: ", message);
  mt_setcursorvisible (true);
  scanf ("%s", path);
  mt_setcursorvisible (false);
  mt_gotoXY (POS_MESSAGE_X, POS_MESSAGE_Y);
  printf ("                                                ");
}

bool
readkeyHandler ()
{
  enum Keys key;
  rk_readKey (&key);

  switch (key)
    {
    case KEY_ESC:
      return true;

    case KEY_UP:
      moveCursor (0);
      return false;
    case KEY_RIGHT:
      moveCursor (1);
      return false;
    case KEY_DOWN:
      moveCursor (2);
      return false;
    case KEY_LEFT:
      moveCursor (3);
      return false;
    case KEY_ENTER:
      startEdit (st_Memory);
      return false;

    case KEY_F5:
      startEdit (st_Accumulator);
      return false;

    case KEY_F6:
      startEdit (st_Counter);
      return false;

    case KEY_L:
    readInput("Введите файл для загрузки");
    sc_memoryLoad(path);
    return false;

    case KEY_S:
      readInput ("Введите файл для сохранения");
      sc_memorySave (path);
      return false;

    case KEY_I:
      mt_clrscr ();
      computerInit ();
      boxDrawed = false;
      updateInterface ();
      boxDrawed = true;
      return false;

    case KEY_R:
      switchIgnoring ();
      return false;

    case KEY_T:
      CU ();
      return false;

    default:
      return 0;
      break;
    }
}

bool
checkTerminal ()
{
  int width = 0;
  int height = 0;
  mt_getscreensize (&height, &width);

  if (width < MIN_WIDTH || height < MIN_HEIGHT)
    return false;
  else
    return true;
}

void
computerInit ()
{

  sc_memoryInit ();
  sc_regInit ();
  sc_icounterInit ();
  sc_accumulatorInit ();
  termInit ();
  sc_casheInit ();
  sc_regSet (FLAG_T, 1);
  ticks = 0;
  cursor_pos = 0;
  comStage = 0;
}

void
charsInit ()
{
  FILE *file = fopen (charPath, "rb");
  big_chars = (int *)malloc (36 * sizeof (int));
  bc_bigcharread (file, big_chars, 18);
}

bool
mainloop ()
{
  updateInterface ();
  return readkeyHandler ();
}

int
main (int argc, char **argv)
{
  if (!checkTerminal ())
    return -1;
  mt_clrscr ();
  charPath = (argc >= 2) ? argv[1] : "console/font.bin";
  charsInit ();
  computerInit ();

  mt_setcursorvisible (false);
  editStatus = st_None;

  updateInterface ();
  boxDrawed = true;
  signal (SIGALRM, IRC);
  alarm (2);
  while (true)
    if (mainloop ())
      break;

  alarm (0);
  free (big_chars);
  mt_setcursorvisible (true);
  mt_setdefaultcolor ();
  mt_gotoXY (POS_MESSAGE_X, POS_MESSAGE_Y);
}