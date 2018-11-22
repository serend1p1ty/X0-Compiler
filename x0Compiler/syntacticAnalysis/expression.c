#include "../global.h"

/*
 * expression语法分析程序
 */
void expression ()
{
	if (sym == hashsym)	/* sym == '#' */	
	{
		getSym ();
		var ();
		if (sym == eql)
		{
			getSym ();
			expression ();
		}
		else /* 缺少= */
		{
			error (11);
		}
	}
	else if (sym == lparen || sym == number || sym == ident)	/* sym属于first(simple_expr) */
	{
		simple_expr ();
	}
	else /* 缺少#或(或数字或标识符 */
	{
		error (12);
	}
}