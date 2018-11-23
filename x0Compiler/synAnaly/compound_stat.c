#include "../global.h"

/*
 * compound_stat语法分析程序
 */
void compound_stat ()
{
	if (sym == lbrace)
	{
		getSym ();
		statement_list ();
		if (sym == rbrace)
		{
			getSym ();
		}
		else /* 缺少} */
		{
			error (4);
		}
	}
	else /* 缺少{ */
	{
		error (5);
	}
}