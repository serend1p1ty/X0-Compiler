#include "../global.h"

/*
 * function: add a new entry to symbol table
 */
void enter (enum objectKind k, int offset, int size1, int size2)
{
	strcpy (table[iterTable].name, id);
	table[iterTable].kind = k;
	table[iterTable].offset = offset;
	table[iterTable].size1 = size1;
	table[iterTable++].size2 = size2;
}