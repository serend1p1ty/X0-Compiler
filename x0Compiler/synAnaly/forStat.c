#include "../global.h"

/*
 * forStat syntactical analyzer
 */
void forStat ()
{
	int startBreakNum = iterBreakList; /* save the number of break statement to be backfilled before analysing forStat */
	int startContinueNum = iterCtnList; /* save the number of continue statement to be backfilled before analysing forStat */

	if (sym == forsym)
	{
		getSym ();

		if (sym == lparen)
		{
			getSym ();
			expression ();
			int L0 = iterCode; /* jumping label */

			if (sym == semic)
			{
				getSym ();
				expression ();
				int pos1 = iterCode; /* save current value of iterCode for backfilling */
				
				/* the position where program jump to hasn't been determined. we'll backfill it later. */
				gen (jpc, 0, 0); 
				gen (jmp, 0, 0);
				
				int L1 = iterCode; /* jumping label */

				if (sym == semic)
				{
					getSym ();
					expression ();
					gen (jmp, 0, L0);
					int L2 = iterCode; /* jumping label */

					if (sym == rparen)
					{
						getSym ();
						statement ();

						/* backfill continue statement */
						for (int i = startContinueNum; i < iterCtnList; i++)
						{
							int pos = continueList[i];
							code[pos].offset = iterCode;
						}
						iterCtnList = startContinueNum; /* set the value of iterCtnList to the value
														 * that is before analysing forStat */
						
						gen (jmp, 0, L1);
						
						/* backfill the position where program jump to */
						code[pos1].offset = iterCode;
						code[pos1 + 1].offset = L2;
					}
					else /* the lack of ')' */
					{
						error (14);
					}
				}
				else /* the lack of ';' */
				{
					error (10);
				}
			}
			else /* the lack of ';' */
			{
				error (10);
			}
		}
		else /* the lack of '(' */
		{
			error (16);
		}
	}
	else /* the lack of 'for' */
	{
		error (31);
	}

	/* backfill break statement */
	for (int i = startBreakNum; i < iterBreakList; i++)
	{
		int pos = breakList[i];
		code[pos].offset = iterCode;
	}
	iterBreakList = startBreakNum; /* set the value of iterBreakList to the value
									* that is before analysing forStat */
}