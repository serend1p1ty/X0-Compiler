#include "../global.h"

/*
 * exit_stat syntactical analyzer
 */
void exit_stat ()
{
	if (sym == exitsym)
	{
		readSymbol ();

		if (sym == lparen)
		{
			readSymbol ();

			if (sym == intnum)
			{
				readSymbol ();
				gen (lit, 1, intNum, 0);

				if (sym == rparen)
				{
					readSymbol ();

					if (sym == semic)
					{
						readSymbol ();
						gen (opr, 7, 0, 0); /* execute 'exit' function */
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
			else /* the lack of INT number */
			{
				error (8);
			}
		}
		else /* the lack of '(' */
		{
			error (16);
		}
	}
	else /* the lack of 'exit' */
	{
		error (35);
	}
}