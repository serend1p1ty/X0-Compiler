#include "../global.h"

/*
 * WhileStat syntactical analyzer
 */
void WhileStat ()
{
	int startBreakNum = brkNum; /* save the number of 'break' statement to be backfilled before analyzing WhileStat */
	int startContinueNum = ctnNum; /* save the number of 'continue' statement to be backfilled before analyzing WhileStat */

	if (sym == whilesym)
	{
		ReadSymbol ();
		if (sym == lparen)
		{
			int pos1 = codeNum; /* save current value of codeNum */
			ReadSymbol ();
			expression ();
			if (sym == rparen)
			{
				int pos2 = codeNum; /* save current value of codeNum for backfilling */

				/* the position where program jump to hasn't been determined. we'll backfill it later. */
				GenINTCode (jpc, 0, 0);

				ReadSymbol ();
				statement ();

				/* backfill 'continue' statement */
				for (int i = startContinueNum; i < ctnNum; i++)
				{
					int pos = continueList[i];
					code[pos].opr1 = codeNum;
				}
				ctnNum = startContinueNum; /* set the value of ctnNum to the value
											* that is before analyzing WhileStat */

				GenINTCode (jmp, pos1, 0);
				code[pos2].opr1 = codeNum; /* backfill */
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
	else /* the lack of 'while' */
	{
		ErrorHandler (20);
	}

	/* backfill 'break' statement */
	for (int i = startBreakNum; i < brkNum; i++)
	{
		int pos = breakList[i];
		code[pos].opr1 = codeNum;
	}
	brkNum = startBreakNum; /* set the value of brkNum to the value
							 * that is before analyzing WhileStat */
}