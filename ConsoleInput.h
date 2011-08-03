#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include <conio.h>

/** Platform specific key constants */
const static int ARROW_CONSTANT = 224;
const static int KEY_ESCAPE = 251;
const static int KEY_LEFT_ARROW = ARROW_CONSTANT + 75;
const static int KEY_RIGHT_ARROW = ARROW_CONSTANT + 77;
const static int KEY_UP_ARROW = ARROW_CONSTANT + 72;
const static int KEY_DOWN_ARROW = ARROW_CONSTANT + 80;

/** Blocks until a keypress occurs, and returns the pressed key */
int getNextKeypress();

#endif