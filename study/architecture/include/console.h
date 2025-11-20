#pragma once

#include "../console/ui_variables.h"
#include "../mySimpleComputer/sc_variables.h"
#include <math.h>
#include <myBigChars.h>
#include <myReadKey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <signal.h>
#include <stdbool.h>

#define MIN_WIDTH 108
#define MIN_HEIGHT 25

#define POS_MEMORY_X 0
#define POS_MEMORY_Y 0

#define POS_ACC_X 61
#define POS_ACC_Y 0

#define POS_FLAG_X 84
#define POS_FLAG_Y 0

#define POS_COUNTER_X 61
#define POS_COUNTER_Y 3

#define POS_COMMAND_X 84
#define POS_COMMAND_Y 3

#define POS_BIG_X 61
#define POS_BIG_Y 6

#define POS_EDIT_X 0
#define POS_EDIT_Y 15

#define POS_TERM_X 66
#define POS_TERM_Y 18

#define POS_CASH_X 0
#define POS_CASH_Y 18

#define POS_KEY_X 77
#define POS_KEY_Y 18

#define POS_MESSAGE_X 0
#define POS_MESSAGE_Y 25

enum EditStatus
{
  st_None,
  st_Memory,
  st_Accumulator,
  st_Counter
};

void ui_accum (int x, int y);
void ui_big (int x, int y);
void ui_command (int x, int y);
void ui_counter (int x, int y);
void ui_editCell (int x, int y);
void ui_flags (int x, int y);
void ui_keys (int x, int y);
void ui_memory (int x, int y);
void ui_term (int x, int y);
void ui_cashe (int x, int y);

void updateInterface ();
void startEdit (enum EditStatus status);

void IRC (int signum);
void CU ();
void ALU (int command, int operand);

int getNormalInt (int memoryInt);
int getMemoryInt (int normal);
bool checkMemoryRange (int value);
