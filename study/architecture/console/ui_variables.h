#pragma once

#include "../include/console.h"
#include <stdbool.h>

extern bool boxDrawed;

// font variables
extern int *big_chars;
extern char *charPath;
extern char path[100];

// edit variables
extern int cursor_pos;

extern enum EditStatus editStatus;

extern bool interactiveMode;

extern int comStage;

extern int cuTemp[20];