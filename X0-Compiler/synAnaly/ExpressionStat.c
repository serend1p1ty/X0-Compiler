#include "../global.h"

/*
 * ExpressionStat syntactical analyzer
 */
void ExpressionStat ()
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
			ReadSymbol ();
		}
		else /* the lack of ';' */
		{
			ErrorHandler (10);
		}
	}
	else if (sym == semic)
	{
		ReadSymbol ();
	}
	else /* sym isn't belong to first(ExpressionStat) */
	{
		ErrorHandler (13);
	}
}