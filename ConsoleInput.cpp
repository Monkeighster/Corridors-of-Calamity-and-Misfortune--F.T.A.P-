#include "ConsoleInput.h"

int getNextKeypress() 
{
	int keyVal = getch();
	if(keyVal = ARROW_CONSTANT) {
		keyVal = keyVal + getch();
	}
	return keyVal;
}