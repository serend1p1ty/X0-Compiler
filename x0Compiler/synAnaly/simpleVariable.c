#include "../global.h"

/*
 * simpleVariable语法分析程序
 */
void simpleVariable (int* ptr_offset, int* ptr_isArray)
{
	if (sym == ident)
	{
		int pos = findPosition (id);

		if (pos == -1)	/* 标识符未声明 */
		{
			error (24);
		}

		getSym ();

		if (sym == lbracket)
		{
			getSym ();
			expression ();

			if (sym == rbracket)
			{
				/* 标识符不是int或char数组 */
				if (table[pos].kind != intArray && table[pos].kind != charArray)
				{
					error (26);
				}

				*ptr_offset = table[pos].offset;
				*ptr_isArray = 1;
				getSym ();
			}
			else /* 缺少] */
			{
				error (9);
			}
		}
		else
		{
			/* 标识符不是int或char变量 */
			if (table[pos].kind != intVar && table[pos].kind != charVar)
			{
				error (25);
			}

			*ptr_offset = table[pos].offset;
			*ptr_isArray = 0;
		}
	}
	else /* 缺少标识符 */
	{
		error (6);
	}
}