#include "../global.h"

/*
 * 查找标识符在符号表中的位置, 找到则返回在符号表中的位置, 否则返回-1
 * identName: 要查找的名字
 */
int findPosition (char* identName)
{
	for (int i = 0; i < iterTable; i++)
	{
		if (strcmp (table[i].name, identName) == 0)
		{
			return i;
		}
	}
	return -1;
}