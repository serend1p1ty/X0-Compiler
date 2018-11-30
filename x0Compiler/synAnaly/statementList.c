#include "../global.h"

/*
 * statementList语法分析程序
 */
void statementList ()
{
	/* 如果sym属于first(statement)就执行statement分析程序 */
	while (sym == ifsym || sym == whilesym || sym == readsym
		|| sym == writesym || sym == lbrace || sym == semic
		|| sym == ident || sym == lparen || sym == number
		|| sym == hashsym || sym == minus || sym == forsym
		|| sym == incsym || sym == decsym || sym == oddsym
		|| sym == notsym || sym == brksym || sym == exitsym
		|| sym == ctnsym || sym == swtcsym || sym == dosym 
		|| sym == reptsym || sym == truesym || sym == falsesym)
	{
		statement ();
	}
}