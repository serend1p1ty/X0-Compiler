#include "../global.h"

/*
 * while语句语法分析程序
 */
void while_stat ()
{
	if (sym == whilesym)
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
	else /* 缺少while */
	{
		error (21);
	}
}