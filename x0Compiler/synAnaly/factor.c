#include "../global.h"

/*
 * factor语法分析程序
 */
void factor ()
{
	if (sym == lparen)
	{
		getSym ();
		expression ();
		if (sym == rparen)
		{
			getSym ();
		}
		else /* 缺少) */
		{
			error (14);
		}
	}
	else if (sym == ident)
	{
		int offset;
		int isArray;
		var (&offset, &isArray); /* 通过传地址的方式知道：变量在活动记录中的偏移、该变量是否是数组 */

		/* 根据是单变量还是数组选择不同的load方式 */
		if (isArray)
		{
			gen (lodf, 0, offset);
		}
		else
		{
			gen (lod, 0, offset);
		}
	}
	else if (sym == number)
	{
		gen (lit, 0, num);
		getSym ();
	}
	else /* 缺少(或标识符或数字 */
	{
		error (15);
	}
}