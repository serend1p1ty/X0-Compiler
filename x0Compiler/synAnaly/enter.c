#include "../global.h"

/*
 * function: add a new entry to symbol table
 */
void enter (enum objectKind k, int offset, int* size, int dimension, double value)
{
	int iterator = iterators[tableNum];

	strcpy (functionTable[tableNum][iterator].name, id);
	functionTable[tableNum][iterator].kind = k;
	functionTable[tableNum][iterator].offset = offset;
	for (int i = 0; i < dimension; i++)
	{
		functionTable[tableNum][iterator].size[i] = size[i];
	}
	functionTable[tableNum][iterator].dimension = dimension;
	functionTable[tableNum][iterator].value = value;

	iterators[tableNum]++;
}