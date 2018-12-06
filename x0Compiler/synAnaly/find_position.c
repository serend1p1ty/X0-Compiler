#include "../global.h"

/*
 * input: identName  the name of identifier which we want to search
 * output: the position of this identifier in symbol table
 */
int find_position_v1 (char* identName)
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

/*
* input: offset  the offset of identifier which we want to search
* output: the position of this identifier in symbol table
*/
int find_position_v2 (int offset)
{
	for (int i = 0; i < iterTable; i++)
	{
		if (table[i].offset == offset)
		{
			return i;
		}
	}
	return -1;
}