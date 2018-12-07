#include "../global.h"

/*
 * WhileStat syntactical analyzer
 */
void WhileStat ()
{
	int startBreakNum = iterBreakList; /* save the number of break statement to be backfilled before analysing WhileStat */
	int startContinueNum = iterCtnList; /* save the number of continue statement to be backfilled before analysing WhileStat */

	if (sym == whilesym)
	{
		ReadSymbol ();

		if (sym == lparen)
		{
			int pos1 = iterCode; /* save current value of iterCode */

			ReadSymbol ();
			expression ();

			if (sym == rparen)
			{
				int pos2 = iterCode; /* save current value of iterCode for backfilling */

				/* the position where program jump to hasn't been determined. we'll backfill it later. */
				GenerateINTCode (jpc, 0, 0, 0);

				ReadSymbol ();
				statement ();

				/* backfill continue statement */
				for (int i = startContinueNum; i < iterCtnList; i++)
				{
					int pos = continueList[i];
					code[pos].operand1 = iterCode;
				}
				iterCtnList = startContinueNum; /* set the value of iterCtnList to the value
												 * that is before analysing WhileStat */

				GenerateINTCode (jmp, pos1, 0, 0);
				code[pos2].operand1 = iterCode; /* backfill */
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
		ErrorHandler (21);
	}

	/* backfill break statement */
	for (int i = startBreakNum; i < iterBreakList; i++)
	{
		int pos = breakList[i];
		code[pos].operand1 = iterCode;
	}
	iterBreakList = startBreakNum; /* set the value of iterBreakList to the value
									* that is before analysing WhileStat */
}