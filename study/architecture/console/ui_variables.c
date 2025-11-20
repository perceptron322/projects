#include "../include/console.h"

bool boxDrawed = false;

// font variables
int *big_chars;
char *charPath;
char path[100];

// edit variables
int cursor_pos = 20;
bool interactiveMode = false;

enum EditStatus editStatus = st_None;

int comStage = 0;
int cuTemp[20];
