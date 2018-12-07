#include "../global.h"

/*
 * input: identName  the name of identifier which we want to search
 * output: the position of this identifier in symbol table
 */
int find_position_v1 (char* identName, int pos)
{
	for (int i = 0; i < iterators[pos]; i++)
	{
		if (strcmp (functionTable[pos][i].name, identName) == 0)
		{
			return i;
		}
	}
	return -1;
}

/*
* input: offset  the offset of identifier which we want to search
* output: the position of this identifier in symbol table
*/
int find_position_v2 (int offset, int pos)
{
	for (int i = 0; i < iterators[pos]; i++)
	{
		if (functionTable[pos][i].offset == offset)
		{
			return i;
		}
	}
	return -1;
}

int find_position_v3 (char* fctName)
{
	for (int i = 0; i < iterFctInfo; i++)
	{
		if (strcmp (fctInfo[i].name, fctName) == 0)
		{
			return i;
		}
	}
	return -1;
}