#include "../global.h"

/*
 * expression语法分析程序
 */
void expression ()
{
	if (sym == hashsym)	/* sym == '#' */	
	{
		getSym ();

		int offset;
		int isArray;
		var (&offset, &isArray); /* 通过传地址的方式知道：变量在活动记录中的偏移、该变量是否是数组 */

		if (sym == eql)
		{
			getSym ();
			expression ();

			/* 根据是单变量还是数组选择不同的store方式 */
			if (isArray)
			{
				gen (stof, 0, offset);
			}
			else
			{
				gen (sto, 0, offset);
			}
		}
		else /* 缺少= */
		{
			error (11);
		}
	}
	else if (sym == lparen || sym == number || sym == ident || sym == minus)	/* sym属于first(simple_expr) */
	{
		simple_expr ();
	}
	else /* 缺少#或(或数字或标识符 */
	{
		error (12);
	}
}