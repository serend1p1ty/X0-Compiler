#include "../global.h"

/*
 * breakStat语法分析程序
 */
void breakStat ()
{
	if (sym == brksym)
	{
		getSym ();

		if (sym == semic)
		{
			getSym ();
			gen (jmp, 0, 0);
			breakList[iterBreakList++] = iterCode - 1;
		}
		else /* 缺少; */
		{
			error (10);
		}
	}
	else /* 缺少break */
	{
		error (34);
	}
}