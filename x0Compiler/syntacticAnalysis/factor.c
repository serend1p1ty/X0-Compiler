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
		var ();
	}
	else if (sym == number)
	{
		getSym ();
	}
	else /* 缺少(或标识符或数字 */
	{
		error (15);
	}
}