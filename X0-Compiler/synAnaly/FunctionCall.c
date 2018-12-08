#include "../global.h"

/*
 * FunctionCall syntactical analyzer
 */
void FunctionCall ()
{
	if (sym == ident)
	{
		int pos = FindPosition_V3 (id);

		if (pos == -1) /* the function hasn't been declared */
		{
			ErrorHandler (56);
		}

		ReadSymbol ();
		if (sym == lparen)
		{
			ReadSymbol ();

			/* the function has a parameter at least if sym belong to first(expression) */
			if (sym == ident || sym == lparen || sym == intnum
				|| sym == minus || sym == incsym || sym == decsym
				|| sym == oddsym || sym == notsym || sym == truesym
				|| sym == falsesym || sym == doublenum)
			{
				expression ();
				while (sym == comma)
				{
					ReadSymbol ();
					expression ();
				}
			}

			if (sym == rparen)
			{
				ReadSymbol ();

				/* function call */
				GenerateINTCode (cal, fctInfo[pos].startINTCode, 0, 0);
			}
			else /* the lack of ')' */
			{
				ErrorHandler (14);
			}
		}
		else /* the lack of '(' */
		{
			ErrorHandler (16);
		}
	}
}