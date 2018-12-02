#include "../global.h"

/*
 * input: 
 * k: type of symbol(charVar/intVar/charArray/intArray)
 * offset: offset of local variable relative to the base address
 * size: the space distributed
 * function: add a new entry to symbol table
 */
void enter (enum objectKind k, int offset, int size)
{
	strcpy (table[iterTable].name, id);
	table[iterTable].kind = k;
	table[iterTable].offset = offset;
	table[iterTable++].size = size;
}