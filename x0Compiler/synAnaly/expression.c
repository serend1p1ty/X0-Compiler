#include "../global.h"

/*
 * expression语法分析程序
 */
void expression ()
{
	if (sym == hashsym)	/* sym == '#' */	
	{
		getSym ();

		/* 
		 * 通过传地址的方式知道：变量在活动记录中的偏移、该变量是否是数组、该变量是否自增/减
		 * (IncOrDec：1后自增、2后自减、3前自增、4前自减、5无增减)
		 */
		int offset;
		int isArray;
		int IncOrDec;
		variable (&offset, &isArray, &IncOrDec);

		/* 赋值语句左边不能是自增或者自减变量 */
		if (IncOrDec != 5)
		{
			error (32);
		}

		if (sym == eql)
		{
			getSym ();
			expression ();

			/* 将expression的值存储到var里 */
			if (isArray)
			{
				gen (stf, 0, offset);
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
	else if (sym == lparen || sym == number || sym == ident || sym == minus
			|| sym == incsym || sym == decsym || sym == oddsym || sym == notsym)	/* sym属于first(valueExpr) */
	{
		valueExpr ();
	}
	else /* 缺少#或标识符或(或数字或-或++或--或odd或! */
	{
		error (12);
	}
}