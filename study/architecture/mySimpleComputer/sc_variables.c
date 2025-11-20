#include "sc_variables.h"
#include "../include/mySimpleComputer.h"
#include <stdio.h>
#include <stdlib.h>

int memory[MEMORY_SIZE];
int accumulator;
int commandCounter;
int flagRegister;

int term_adress[5];
int term_input[5];
int term_val[5];

int cashe[5][10];
int casheNum[5];

int ticks = 0;