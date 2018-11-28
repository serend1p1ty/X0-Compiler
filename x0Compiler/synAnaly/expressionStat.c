#include "../global.h"

/*
 * expressionStat语法分析程序
 */
void expressionStat ()
{
	/* 如果sym属于first(expression)，就执行expression语法分析程序 */
	if (sym == hashsym || sym == ident|| sym == lparen 
		|| sym == number || sym == minus || sym == incsym 
		|| sym == decsym || sym == oddsym || sym == notsym)
	{
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
	else if (sym == semic)
	{
		getSym ();
	}
	else /* 缺少#或标识符或(或数字或-或++或--或odd或!或; */
	{
		error (13);
	}
}