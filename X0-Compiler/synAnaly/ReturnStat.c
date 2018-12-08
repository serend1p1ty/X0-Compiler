#include "../global.h"

/*
 * ReturnStat syntactical analyzer
 */
void ReturnStat ()
{
	if (sym == retsym)
	{
		ReadSymbol ();

		if (sym == lparen || sym == intnum || sym == ident || sym == minus
			|| sym == incsym || sym == decsym || sym == oddsym || sym == notsym
			|| sym == truesym || sym == falsesym || sym == doublenum || sym == ident) /* sym belong to first(ValueExpr) */
		{
			ValueExpr ();
		}

		if (sym == semic)
		{
			ReadSymbol ();
			GenerateINTCode (opr, 0, iterFctInfo, 0);
		}
		else /* the lack of ';' */
		{
			ErrorHandler (10);
		}
	}
}