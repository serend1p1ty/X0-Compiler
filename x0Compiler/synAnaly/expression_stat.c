#include "../global.h"

/*
 * expression_stat syntactical analyzer
 */
void expression_stat ()
{
	/* execute expression syntactical analyzer if sym belong to first(expression) */
	if (sym == ident|| sym == lparen || sym == intnum 
		|| sym == minus || sym == incsym || sym == decsym 
		|| sym == oddsym || sym == notsym || sym == truesym 
		|| sym == falsesym || sym == doublenum)
	{
		expression ();

		if (sym == semic)
		{
			readSymbol ();
		}
		else /* the lack of ';' */
		{
			error (10);
		}
	}
	else if (sym == semic)
	{
		readSymbol ();
	}
	else /* sym isn't belong to first(expression_stat) */
	{
		error (13);
	}
}