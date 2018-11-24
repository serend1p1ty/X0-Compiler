#include "../global.h"

/*
 * statement语法分析程序
 */
void statement ()
{
	if (sym == ifsym)	/* if语句 */
	{
		if_stat ();
	}
	else if (sym == whilesym)	/* while语句 */
	{
		while_stat ();
	}
	else if (sym == readsym)	/* read语句 */
	{
		read_stat ();
	}
	else if (sym == writesym)	/* write语句 */
	{
		write_stat ();
	}
	else if (sym == lbrace)	/* compound语句 */
	{
		compound_stat ();
	}
	else if (sym == semic || sym == ident || sym == hashsym
		|| sym == lparen || sym == number || sym == minus)	/* expression语句 */
	{
		expression_stat ();
	}
	else if (sym == forsym) /* for语句 */
	{
		for_stat ();
	}
	else /* 缺少if或while或read或write或{或;或标识符或数字或#或( */
	{
		error (19);
	}
}