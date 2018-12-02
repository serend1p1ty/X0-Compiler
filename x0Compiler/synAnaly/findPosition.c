#include "../global.h"

/*
 * input: identName  the name of identifier which we want to search
 * output: the position of this identifier in symbol table
 */
int findPosition (char* identName)
{
	for (int i = 0; i < iterTable; i++)
	{
		if (strcmp (table[i].name, identName) == 0)
		{
			return i;
		}
	}
	return -1;
}