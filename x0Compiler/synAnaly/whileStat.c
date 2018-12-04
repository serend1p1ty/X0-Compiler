#include "../global.h"

/*
 * whileStat syntactical analyzer
 */
void whileStat ()
{
	int startBreakNum = iterBreakList; /* save the number of break statement to be backfilled before analysing whileStat */
	int startContinueNum = iterCtnList; /* save the number of continue statement to be backfilled before analysing whileStat */

	if (sym == whilesym)
	{
		getSym ();

		if (sym == lparen)
		{
			int pos1 = iterCode; /* save current value of iterCode */

			getSym ();
			expression ();

			if (sym == rparen)
			{
				int pos2 = iterCode; /* save current value of iterCode for backfilling */
				gen (jpc, 0, 0, 0); /* the position where program jump to hasn't been determined. we'll backfill it later. */
				getSym ();
				statement ();

				/* backfill continue statement */
				for (int i = startContinueNum; i < iterCtnList; i++)
				{
					int pos = continueList[i];
					code[pos].operand1 = iterCode;
				}
				iterCtnList = startContinueNum; /* set the value of iterCtnList to the value
												 * that is before analysing whileStat */

				gen (jmp, pos1, 0, 0);
				code[pos2].operand1 = iterCode; /* backfill */
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
	else /* the lack of 'while' */
	{
		error (21);
	}

	/* backfill break statement */
	for (int i = startBreakNum; i < iterBreakList; i++)
	{
		int pos = breakList[i];
		code[pos].operand1 = iterCode;
	}
	iterBreakList = startBreakNum; /* set the value of iterBreakList to the value
									* that is before analysing whileStat */
}