#include "../global.h"

/*
 * function: add a new entry to symbol table
 */
void enter (enum objectKind k, int offset, int* size, int dimension, double value)
{
	strcpy (table[iterTable].name, id);
	table[iterTable].kind = k;
	table[iterTable].offset = offset;
	for (int i = 0; i < dimension; i++)
	{
		table[iterTable].size[i] = size[i];
	}
	table[iterTable].dimension = dimension;
	table[iterTable++].value = value;
}