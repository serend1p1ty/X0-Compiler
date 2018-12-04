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
			
			if (sym != semic)
			{
				expression ();
			}

			if (sym == semic)
			{
				getSym ();
				int L0 = iterCode; /* jumping label */

				int pos1;
				int isEmpty = 1; /* isEmpty = 1 means judgement statement is empty */
				if (sym != semic)
				{
					isEmpty = 0;
					expression ();
					pos1 = iterCode; /* save current value of iterCode for backfilling */
					gen (jpc, 0, 0, 0); /* the position where program jump to hasn't been determined. 
									     * we'll backfill it later */
				}
				else
				{
					pos1 = iterCode;
				}

				gen (jmp, 0, 0, 0); /* the position where program jump to hasn't been determined. 
							         * we'll backfill it later */

				if (sym == semic)
				{
					getSym ();
					int L1 = iterCode; /* jumping label */

					if (sym != rparen)
					{
						expression ();
					}
					
					gen (jmp, L0, 0, 0);

					if (sym == rparen)
					{
						getSym ();
						int L2 = iterCode; /* jumping label */
						statement ();

						/* backfill continue statement */
						for (int i = startContinueNum; i < iterCtnList; i++)
						{
							int pos = continueList[i];
							code[pos].operand1 = iterCode;
						}
						iterCtnList = startContinueNum; /* set the value of iterCtnList to the value
														 * that is before analysing forStat */
						
						gen (jmp, L1, 0, 0);
						
						/* backfill the position where program jump to */
						if (!isEmpty)
						{
							code[pos1].operand1 = iterCode;
							code[pos1 + 1].operand1 = L2;
						}
						else
						{
							code[pos1].operand1 = L2;
						}
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
		code[pos].operand1 = iterCode;
	}
	iterBreakList = startBreakNum; /* set the value of iterBreakList to the value
									* that is before analysing forStat */
}