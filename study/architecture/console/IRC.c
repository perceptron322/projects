#include "../include/console.h"

void
IRC (int signum)
{
  int ignore;
  switch (signum)
    {
    case SIGALRM:

      sc_regGet (FLAG_T, &ignore);

      if (ignore)
        {
          alarm (2);
          return;
        }

      CU ();
      alarm (2);
      updateInterface ();
      break;

    case SIGUSR1:
      // todo
      break;
    default:
      break;
    }
}