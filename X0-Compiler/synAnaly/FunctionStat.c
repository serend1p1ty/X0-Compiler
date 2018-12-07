#include "../global.h"

/*
 * FunctionStat syntactical analyzer
 */
void FunctionStat ()
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
			expression ();
			while (sym == comma)
			{
				ReadSymbol ();
				expression ();
			}
			if (sym == rparen)
			{
				ReadSymbol ();
				if (sym == semic)
				{
					/* function call */
					GenerateINTCode (cal, fctInfo[pos].startINTCode, 0, 0);
					
					ReadSymbol ();
				}
				else /* the lack of ';' */
				{
					ErrorHandler (10);
				}
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