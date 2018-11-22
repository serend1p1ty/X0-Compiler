#include "../global.h"

/*
 * if语句语法分析程序
 */
void if_stat ()
{
	if (sym == ifsym)
	{
		getSym ();
		if (sym == lparen)
		{
			getSym ();
			expression ();
			if (sym == rparen)
			{
				getSym ();
				statement ();
				if (sym == elsesym)
				{
					getSym ();
					statement ();
				}
			}
			else /* 缺少) */
			{
				error (14);
			}
		}
		else /* 缺少( */
		{
			error (16);
		}
	}
	else /* 缺少if */
	{
		error (17);
	}
}