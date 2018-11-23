#include "../global.h"

/*
 * statement_list语法分析程序
 */
void statement_list ()
{
	/* 如果sym属于first(statement)就执行statement分析程序 */
	while (sym == ifsym || sym == whilesym || sym == readsym
		|| sym == writesym || sym == lbrace || sym == semic
		|| sym == ident || sym == lparen || sym == number || sym == hashsym)
	{
		statement ();
	}
}