#include "../global.h"

/*
 * IfStat syntactical analyzer
 */
void IfStat ()
{
	if (sym == ifsym)
	{
		ReadSymbol ();
		if (sym == lparen)
		{
			ReadSymbol ();
			expression ();
			int pos1 = iterCode; /* save current value of iterCode for backfilling */

			/* the position where program jump to hasn't been determined. we'll backfill it later. */
			GenerateINTCode (jpc, 0, 0, 0);

			if (sym == rparen)
			{
				ReadSymbol ();
				statement ();

				if (sym == elsesym)
				{
					int pos2 = iterCode; /* save current value of iterCode for backfilling */
					
					/* the position where program jump to hasn't been determined. we'll backfill it later. */
					GenerateINTCode (jmp, 0, 0, 0);
					
					code[pos1].operand1 = iterCode; /* backfill */
					ReadSymbol ();
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
				ErrorHandler (14);
			}
		}
		else /* the lack of '(' */
		{
			ErrorHandler (16);
		}
	}
	else /* the lack of 'if' */
	{
		ErrorHandler (17);
	}
}