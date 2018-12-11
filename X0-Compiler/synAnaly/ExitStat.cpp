#include "../global.h"

/*
 * ExitStat syntactical analyzer
 */
void ExitStat ()
{
	if (sym == exitsym)
	{
		ReadSymbol ();
		if (sym == lparen)
		{
			ReadSymbol ();
			if (sym == intnum)
			{
				ReadSymbol ();
				GenINTCode (lit, intNum, 0);
				if (sym == rparen)
				{
					ReadSymbol ();
					if (sym == semic)
					{
						ReadSymbol ();
						GenINTCode (opr, 7, 0); /* execute 'exit' function */
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
			else /* the lack of integer */
			{
				ErrorHandler (8);
			}
		}
		else /* the lack of '(' */
		{
			ErrorHandler (16);
		}
	}
	else /* the lack of 'exit' */
	{
		ErrorHandler (34);
	}
}