#include "../global.h"

/*
 * write语句语法分析程序
 */
void write_stat ()
{
	if (sym == writesym)
	{
		getSym ();
		expression ();
		if (sym == semic)
		{
			getSym ();
		}
		else /* 缺少; */
		{
			error (10);
		}
	}
	else /* 缺少write */
	{
		error (22);
	}
}