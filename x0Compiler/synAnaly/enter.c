#include "../global.h"

/*
 * 在符号表中加入一项
 * k: 符号的类型(charVar/intVar/charArray/intArray)
 * offset: 局部变量相对于活动记录开始位置的偏移
 * size: 分配的空间大小
 */
void enter (enum objectKind k, int offset, int size)
{
	strcpy (table[iterTable].name, id); /* 符号表的name域记录标识符的名字 */
	table[iterTable].kind = k;
	table[iterTable].offset = offset;
	table[iterTable++].size = size;
}