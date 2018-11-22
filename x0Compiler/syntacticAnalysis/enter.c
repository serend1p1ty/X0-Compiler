#include "../global.h"

/*
 * 在符号表中加入一项
 * k: 符号的类型(charVar/intVar/charArray/intArray)
 */
void enter (enum objectKind k)
{
	strcpy (table[iterTable].name, id); /* 符号表的name域记录标识符的名字 */
	table[iterTable++].kind = k;
}