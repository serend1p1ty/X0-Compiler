#include "../global.h"

/*
 * function: add a new entry to symbol table
 */
void EnterTable (ObjectKind k, int offset, int* size, int d, double value)
{
	int& tableSize = fctInfo[fctNum - 1].tableSize;
	TableObject (&table)[MAX_SIZE_TABLE] = fctInfo[fctNum - 1].symTable;

	strcpy (table[tableSize].name, id);
	table[tableSize].kind = k;
	table[tableSize].offset = offset;
	for (int i = 0; i < d; i++)
	{
		table[tableSize].size[i] = size[i];
	}
	table[tableSize].d = d;
	table[tableSize].value = value;

	tableSize++;
}