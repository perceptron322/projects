#include "../include/console.h"
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

void
command_CPUINFO ()
{
  mt_gotoXY (POS_MESSAGE_X, POS_MESSAGE_Y);
  printf ("Парфенов Максим Юрьевич ИВ - 321");
  sc_icounterIncrement ();
}

void
command_READ (int adr)
{
  mt_setcursorvisible (1);
  rk_mytermrestore ();
  alarm (0); // Отключаем таймер

  int value = 0;
  bool input_valid = false;

  // Цикл ввода значения
  while (!input_valid)
    {
      // Очищаем область ввода
      mt_gotoXY (POS_MESSAGE_X, POS_MESSAGE_Y);
      printf ("                                                         ");

      // Запрашиваем ввод
      mt_gotoXY (POS_MESSAGE_X, POS_MESSAGE_Y);
      printf ("Ввод активирован: ");

      // Считываем ввод
      char input_buffer[100];
      while ((getchar ()) != '\n')
        ;
      if (fgets (input_buffer, sizeof (input_buffer), stdin) == NULL)
        {
          // Обработка ошибки ввода
          clearerr (stdin);
          continue;
        }

      // Парсим ввод
      char *endptr;
      errno = 0;
      long temp_value = strtol (input_buffer, &endptr, 10);

      value = (int)temp_value;
      sc_memorySet (adr, value);
      input_valid = true;
    }

  // Очищаем область сообщения
  mt_gotoXY (POS_MESSAGE_X, POS_MESSAGE_Y);
  printf ("                                                         ");

  // Получаем значение из памяти и устанавливаем его
  value = getMemoryInt (value);
  if (mk_Set (adr, value) == -1)
    {
      return; // Ошибка установки значения
    }

  // Восстанавливаем настройки терминала
  mt_setcursorvisible (0);
  rk_mytermregime (1, 0, 1, 0, 1);

  // Обновляем состояние
  addTerm (adr, 1);
  sc_icounterIncrement ();
  alarm (2); // Восстанавливаем таймер
  updateInterface ();
}

void
command_WRITE (int adr)
{
  int temp;
  // sc_memoryGet (adr, &temp);
  if (mk_get (adr, &temp) == -1)
    return;

  mt_gotoXY (POS_MESSAGE_X, POS_MESSAGE_Y);
  printf ("Вывод: %d", getNormalInt (temp));
  sc_icounterIncrement ();
  addTerm (adr, 0);
}

void
command_LOAD (int adr)
{
  int temp;
  // sc_memoryGet (adr, &temp);
  if (!mk_get (adr, &temp) == 0)
    {
      return;
    }
  sc_accumulatorSet (temp);
  sc_icounterIncrement ();
}

void
command_STORE (int adr)
{
  int temp;
  sc_accumulatorGet (&temp);

  sc_memorySet (adr, temp);
  sc_icounterIncrement ();
}

void
command_JNEG (int adr)
{
  sc_accumulatorGet (&cuTemp[0]);
  if (getNormalInt (cuTemp[0]) < 0)
    {
      sc_icounterSet (adr);
    }
  else
    {
      sc_icounterIncrement ();
    }
  ticks--;
}

void
command_JZ (int adr)
{
  int temp;
  sc_accumulatorGet (&temp);
  if (getNormalInt (temp) == 0)
    {
      sc_icounterSet (adr);
    }
  else
    {
      sc_icounterIncrement ();
    }
}

void
command_ASSIGN1 (int adr)
{
  sc_memorySet(adr, 1);
  sc_icounterIncrement ();
}

void
command_LOGLC (int adr)
{
  int accumNum;
  int memNum;
  int result;
  sc_accumulatorGet(&accumNum);
  sc_memoryGet(adr, &memNum);
  result = memNum << accumNum;
  sc_accumulatorSet(result);

  sc_icounterIncrement();
}

void
command_LOGRC (int adr)
{
  int accumNum;
  int memNum;
  int result;
  sc_accumulatorGet(&accumNum);
  sc_memoryGet(adr, &memNum);
  result = memNum >> accumNum;
  sc_accumulatorSet(result);

  sc_icounterIncrement();
}


void
CU ()
{

  // check all flags
  int flags[4] = { 0, 0, 0, 0 };
  sc_regGet (FLAG_P, &flags[0]);
  sc_regGet (FLAG_0, &flags[1]);
  sc_regGet (FLAG_M, &flags[2]);
  sc_regGet (FLAG_E, &flags[3]);

  for (int i = 0; i < 4; i++)
    if (flags[i] == 1)
      {
        sc_regSet (FLAG_T, 1);
        return;
      }
  // get command and operand
  int sign, command, operand, counter, cell;
  sc_icounterGet (&counter);
  sc_memoryGet (counter, &cell);
  sc_commandDecode (cell, &sign, &command, &operand);

  if (sign == 1)
    {
      sc_icounterIncrement ();
      return;
    }
  if (sc_commandValidate (command) == -1)
    {
      sc_regSet (FLAG_E, 1);
      sc_regSet (FLAG_T, 1);
      sc_icounterIncrement ();
      return;
    }

  // check ALU command
  if (command >= 30 && command < 34)
    ALU (command, operand);

  // CU commands
  switch (command)
    {
    case C_NOP:
      sc_icounterIncrement ();
      ticks++;
      break;
    case C_CPUINFO:
      command_CPUINFO ();
      ticks++;
      break;

    case C_READ:
      command_READ (operand);
      ticks += 10;
      break;
    case C_WRITE:
      command_WRITE (operand);
      ticks++;
      break;

    case C_LOAD:
      command_LOAD (operand);
      break;
    case C_STORE:
      command_STORE (operand);
      ticks += 10;
      break;

    case C_JUMP:
      sc_icounterSet (operand);
      ticks++;
      break;
    case C_JNEG:
      command_JNEG (operand);
      ticks++;
      break;
    case C_JZ:
      command_JZ (operand);
      ticks++;
      break;
    case C_HALT:
      sc_regSet (FLAG_T, 1);
      ticks++;
      break;
    case C_ASSIGN1:
      command_ASSIGN1 (operand);
      ticks++;
      break;
    case C_LOGLC:
      command_LOGLC (operand);
      ticks++;
      break;
    case C_LOGRC:
      command_LOGRC (operand);
      ticks++;
      break;

    default:
      break;
    }
  updateInterface ();
}