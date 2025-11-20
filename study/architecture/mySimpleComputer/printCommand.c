#include "../include/mySimpleComputer.h"

// выводит результат декодирования ячейки памяти, адрес которой указан в
// счетчике команд
void
printCommand (void)
{
  int address = 0;
  sc_icounterGet (&address);
  int cell = 0;
  sc_memoryGet (address, &cell);

  int sign = 0;
  int command = 0;
  int operand = 0;

  sc_commandDecode (command, &sign, &command, &operand);

  printf ("%c %02x : %02x", (sign == 1) ? '+' : '-', command, operand);
}
