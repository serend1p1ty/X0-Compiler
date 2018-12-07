#include "../global.h"

/*
 * input:
 * identName: the name of identifier which we want to search
 * pos: index of the symbol table in symTables
 * output: 
 * the position of this identifier in symbol table
 */
int FindPosition_V1 (char* identName, int pos)
{
	for (int i = 0; i < iterators[pos]; i++)
	{
		if (strcmp (symTables[pos][i].name, identName) == 0)
		{
			return i;
		}
	}
	return -1;
}

/*
 * input: 
 * offset: the offset of identifier which we want to search
 * pos: index of the symbol table in symTables
 * output: 
 * the position of this identifier in symbol table
 */
int FindPosition_V2 (int offset, int pos)
{
	for (int i = 0; i < iterators[pos]; i++)
	{
		if (symTables[pos][i].offset == offset)
		{
			return i;
		}
	}
	return -1;
}

/*
 * input: function name
 * output: position of the function in fctInfo
 */
int FindPosition_V3 (char* fctName)
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