#include "../global.h"

/*
 * ForStat syntactical analyzer
 */
void ForStat ()
{
	int startBreakNum = iterBreakList; /* save the number of break statement to be backfilled before analyzing ForStat */
	int startContinueNum = iterCtnList; /* save the number of continue statement to be backfilled before analyzing ForStat */

	if (sym == forsym)
	{
		ReadSymbol ();
		if (sym == lparen)
		{
			ReadSymbol ();

			if (sym != semic)
			{
				expression ();
			}

			if (sym == semic)
			{
				ReadSymbol ();
				int L0 = iterCode; /* jumping label */
				int pos1;
				int isEmpty = 1; /* isEmpty = 1 means judgement statement is empty */
				if (sym != semic)
				{
					isEmpty = 0;
					expression ();
					pos1 = iterCode; /* save current value of iterCode for backfilling */
					GenerateINTCode (jpc, 0, 0, 0); /* the position where program jump to hasn't been determined. 
													 * we'll backfill it later */
				}
				else
				{
					pos1 = iterCode;
				}

				GenerateINTCode (jmp, 0, 0, 0); /* the position where program jump to hasn't been determined. 
												 * we'll backfill it later */

				if (sym == semic)
				{
					ReadSymbol ();
					int L1 = iterCode; /* jumping label */

					if (sym != rparen)
					{
						expression ();
					}
					
					GenerateINTCode (jmp, L0, 0, 0);

					if (sym == rparen)
					{
						ReadSymbol ();
						int L2 = iterCode; /* jumping label */
						statement ();

						/* backfill continue statement */
						for (int i = startContinueNum; i < iterCtnList; i++)
						{
							int pos = continueList[i];
							code[pos].operand1 = iterCode;
						}
						iterCtnList = startContinueNum; /* set the value of iterCtnList to the value
														 * that is before analysing ForStat */
						
						GenerateINTCode (jmp, L1, 0, 0);
						
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
						ErrorHandler (14);
					}
				}
				else /* the lack of ';' */
				{
					ErrorHandler (10);
				}
			}
			else /* the lack of ';' */
			{
				ErrorHandler (10);
			}
		}
		else /* the lack of '(' */
		{
			ErrorHandler (16);
		}
	}
	else /* the lack of 'for' */
	{
		ErrorHandler (31);
	}

	/* backfill break statement */
	for (int i = startBreakNum; i < iterBreakList; i++)
	{
		int pos = breakList[i];
		code[pos].operand1 = iterCode;
	}
	iterBreakList = startBreakNum; /* set the value of iterBreakList to the value
									* that is before analysing ForStat */
}