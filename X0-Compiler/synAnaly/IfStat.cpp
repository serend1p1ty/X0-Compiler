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
			int pos1 = codeNum; /* save current value of codeNum for backfilling */

			/* the position where program jump to hasn't been determined. we'll backfill it later. */
			GenINTCode (jpc, 0, 0);

			if (sym == rparen)
			{
				ReadSymbol ();
				statement ();

				if (sym == elsesym)
				{
					int pos2 = codeNum; /* save current value of codeNum for backfilling */
					
					/* the position where program jump to hasn't been determined. we'll backfill it later. */
					GenINTCode (jmp, 0, 0);
					
					code[pos1].opr1 = codeNum; /* backfill */
					ReadSymbol ();
					statement ();
					code[pos2].opr1 = codeNum; /* backfill */
				}
				else
				{
					code[pos1].opr1 = codeNum; /* backfill */
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