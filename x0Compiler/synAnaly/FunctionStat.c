#include "../global.h"

void FunctionStat ()
{
	if (sym == ident)
	{
		int pos = find_position_v3 (id);
		if (pos == -1)
		{
			error (56);
		}

		readSymbol ();
		if (sym == lparen)
		{
			readSymbol ();
			expression ();
			while (sym == comma)
			{
				readSymbol ();
				expression ();
			}
			if (sym == rparen)
			{
				readSymbol ();
				if (sym == semic)
				{
					gen (cal, fctInfo[pos].startINTCode, 0, 0);
					readSymbol ();
				}
				else /* the lack of ';' */
				{
					error (10);
				}
			}
			else /* the lack of ')' */
			{
				error (14);
			}
		}
		else /* the lack of '(' */
		{
			error (16);
		}
	}
}