#include "../global.h"

/*
 * if_stat syntactical analyzer
 */
void if_stat ()
{
	if (sym == ifsym)
	{
		readSymbol ();

		if (sym == lparen)
		{
			readSymbol ();
			expression ();
			int pos1 = iterCode; /* save current value of iterCode for backfilling */
			gen (jpc, 0, 0, 0);  /* the position where program jump to hasn't been determined. we'll backfill it later. */

			if (sym == rparen)
			{
				readSymbol ();
				statement ();

				if (sym == elsesym)
				{
					int pos2 = iterCode; /* save current value of iterCode for backfilling */
					gen (jmp, 0, 0, 0);  /* the position where program jump to hasn't been determined. we'll backfill it later. */
					code[pos1].operand1 = iterCode; /* backfill */
					readSymbol ();
					statement ();
					code[pos2].operand1 = iterCode; /* backfill */
				}
				else
				{
					code[pos1].operand1 = iterCode; /* backfill */
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
	else /* the lack of 'if' */
	{
		error (17);
	}
}