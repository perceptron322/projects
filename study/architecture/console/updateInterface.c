#include "../include/console.h"

void
updateInterface ()
{
  ui_memory (POS_MEMORY_X, POS_MEMORY_Y);

  ui_accum (POS_ACC_X, POS_ACC_Y);
  ui_flags (POS_FLAG_X, POS_FLAG_Y);

  ui_counter (POS_COUNTER_X, POS_COUNTER_Y);
  ui_command (POS_COMMAND_X, POS_COMMAND_Y);

  ui_editCell (POS_EDIT_X, POS_EDIT_Y);

  ui_big (POS_BIG_X, POS_BIG_Y);

  ui_keys (POS_KEY_X, POS_KEY_Y);
  ui_term (POS_TERM_X, POS_TERM_Y);
  ui_cashe (POS_CASH_X, POS_CASH_Y);
}