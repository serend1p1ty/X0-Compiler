#include "../global.h"

/*
 * input:
 * identName: the name of identifier which we want to search
 * pos: index of the function in fctInfo
 * output: 
 * the position of this identifier in the symbol table of the function
 */
int FindPosition (char* identName, int pos)
{
	for (int i = 0; i < fctInfo[pos].tableSize; i++)
	{
		if (strcmp (fctInfo[pos].symTable[i].name, identName) == 0)
		{
			return i;
		}
	}
	return -1;
}

/*
 * input: 
 * offset: the offset of this identifier which we want to search
 * pos: index of the function in fctInfo
 * output: 
 * the position of this identifier in the symbol table of the function
 */
int FindPosition (int offset, int pos)
{
	for (int i = 0; i < fctInfo[pos].tableSize; i++)
	{
		if (fctInfo[pos].symTable[i].offset == offset)
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
int FindPosition (char* fctName)
{
	for (int i = 0; i < fctNum; i++)
	{
		if (strcmp (fctInfo[i].name, fctName) == 0)
		{
			return i;
		}
	}
	return -1;
}