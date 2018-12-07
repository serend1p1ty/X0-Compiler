#include "../global.h"

/*
 * function: add a new entry to symbol table
 */
void EnterTable (ObjectKind k, int offset, int* size, int dimension, double value)
{
	int iterator = iterators[tableNum];

	strcpy (symTables[tableNum][iterator].name, id);
	symTables[tableNum][iterator].kind = k;
	symTables[tableNum][iterator].offset = offset;
	for (int i = 0; i < dimension; i++)
	{
		symTables[tableNum][iterator].sizeArray[i] = size[i];
	}
	symTables[tableNum][iterator].dimension = dimension;
	symTables[tableNum][iterator].value = value;

	iterators[tableNum]++;
}