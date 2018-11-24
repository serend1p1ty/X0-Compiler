#include "../global.h"

/*
 * expression_stat语法分析程序
 */
void expression_stat ()
{
	/* 如果sym属于first(expression)，就执行expression语法分析程序 */
	if (sym == hashsym || sym == ident|| sym == lparen || sym == number || sym == minus)
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
	else /* 缺少#或标识符或数字或(或; */
	{
		error (13);
	}
}