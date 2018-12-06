#include "../global.h"

/*
 * statementList syntactical analyzer
 */
void statementList ()
{
	/* execute statement syntactical analyzer if sym belong to first(statement) */
	while (sym == ifsym || sym == whilesym || sym == readsym
		|| sym == writesym || sym == lbrace || sym == semic
		|| sym == ident || sym == lparen || sym == intnum
		|| sym == doublenum || sym == minus || sym == forsym
		|| sym == incsym || sym == decsym || sym == oddsym
		|| sym == notsym || sym == brksym || sym == exitsym
		|| sym == ctnsym || sym == swtcsym || sym == dosym 
		|| sym == reptsym || sym == truesym || sym == falsesym)
	{
		statement ();
	}
}