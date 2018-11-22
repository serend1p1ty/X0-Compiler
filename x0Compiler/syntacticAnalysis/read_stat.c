#include "../global.h"

/*
 * read语句语法分析程序
 */
void read_stat ()
{
	if (sym == readsym)
	{
		getSym ();
		var ();
		if (sym == semic)
		{
			getSym ();
		}
		else /* 缺少; */
		{
			error (10);
		}
	}
	else /* 缺少read */
	{
		error (18);
	}
}