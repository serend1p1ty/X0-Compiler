#include "../global.h"

/*
 * expressionStat syntactical analyzer
 */
void expressionStat ()
{
	/* execute expression syntactical analyzer if sym belong to first(expression) */
	if (sym == hashsym || sym == ident|| sym == lparen 
		|| sym == intnum || sym == minus || sym == incsym 
		|| sym == decsym || sym == oddsym || sym == notsym
		|| sym == truesym || sym == falsesym || sym == doublenum)
	{
		expression ();

		if (sym == semic)
		{
			getSym ();
		}
		else /* the lack of ';' */
		{
			error (10);
		}
	}
	else if (sym == semic)
	{
		getSym ();
	}
	else /* sym isn't belong to first(expressionStat) */
	{
		error (13);
	}
}