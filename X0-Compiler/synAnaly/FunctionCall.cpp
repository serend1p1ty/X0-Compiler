#include "../global.h"

/*
 * FunctionCall syntactical analyzer
 */
void FunctionCall ()
{
	if (sym == ident)
	{
		int pos = FindPosition (id);

		if (pos == -1) /* the function hasn't been declared */
		{
			ErrorHandler (55);
		}

		ReadSymbol ();
		if (sym == lparen)
		{
			ReadSymbol ();

			/* the function has a parameter at least if sym != rparen */
			if (sym != rparen)
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
				GenINTCode (cal, fctInfo[pos].startINTCode, 0);
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