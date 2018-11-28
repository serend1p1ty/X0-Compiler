#include "../global.h"

/*
 * compoundStat语法分析程序
 */
void compoundStat ()
{
	if (sym == lbrace)
	{
		getSym ();
		statementList ();
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