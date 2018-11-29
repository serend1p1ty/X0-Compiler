#include "../global.h"

/*
 * continueStat语法分析程序
 */
void continueStat ()
{
	if (sym == ctnsym)
	{
		getSym ();

		if (sym == semic)
		{
			getSym ();
			gen (jmp, 0, 0);
			continueList[iterCtnList++] = iterCode - 1;
		}
		else /* 缺少; */
		{
			error (10);
		}
	}
	else /* 缺少continue */
	{
		error (36);
	}
}