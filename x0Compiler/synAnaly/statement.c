#include "../global.h"

/*
 * statement语法分析程序
 */
void statement ()
{
	if (sym == ifsym)	/* if语句 */
	{
		ifStat ();
	}
	else if (sym == whilesym)	/* while语句 */
	{
		whileStat ();
	}
	else if (sym == readsym)	/* read语句 */
	{
		readStat ();
	}
	else if (sym == writesym)	/* write语句 */
	{
		writeStat ();
	}
	else if (sym == lbrace)	/* compound语句 */
	{
		compoundStat ();
	}
	else if (sym == semic || sym == ident || sym == hashsym
		|| sym == lparen || sym == number || sym == minus
		|| sym == incsym || sym == decsym || sym == oddsym || sym == notsym)	/* expression语句 */
	{
		expressionStat ();
	}
	else if (sym == forsym) /* for语句 */
	{
		forStat ();
	}
	else if (sym == brksym) /* break语句 */
	{
		breakStat ();
	}
	else if (sym == exitsym) /* exit语句 */
	{
		exitStat ();
	}
	else if (sym == ctnsym) /* continue语句 */
	{
		continueStat ();
	}
	else /* 缺少if或while或read或write或{或for或#或标识符或(或数字或-或++或--或odd或!或; */
	{
		error (19);
	}
}