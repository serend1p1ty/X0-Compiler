#include "../global.h"

/*
 * var语法分析程序
 */
void var ()
{
	if (sym == ident)
	{
		/* 保存此时的标识符名字 */
		char tempId[MAX_SIZE_IDENT + 1];
		strcpy (tempId, id);

		getSym ();
		if (sym == lbracket)
		{
			getSym ();
			expression ();
			if (sym == rbracket)
			{
				int pos = findPosition (tempId);
				if (pos == -1)	/* 标识符未声明 */
				{
					error (24);
				}
				/* 标识符不是int或char数组 */
				else if (table[pos].kind != intArray 
					&& table[pos].kind != charArray)
				{
					error (26);
				}

				getSym ();
			}
			else /* 缺少] */
			{
				error (9);
			}
		}
		else
		{
			int pos = findPosition (tempId);
			if (pos == -1)	/* 标识符未声明 */
			{
				error (24);
			}
			/* 标识符不是int或char变量 */
			else if (table[pos].kind != intVar && table[pos].kind != charVar)
			{
				error (25);
			}
		}
	}
	else /* 缺少标识符 */
	{
		error (6);
	}
}