#include "../global.h"

/*
 * ForStat syntactical analyzer
 */
void ForStat ()
{
	int startBreakNum = brkNum; /* save the number of 'break' statement to be backfilled before analyzing ForStat */
	int startContinueNum = ctnNum; /* save the number of 'continue' statement to be backfilled before analyzing ForStat */

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
				int L0 = codeNum; /* jumping label */
				int pos1;
				int isEmpty = 1; /* isEmpty = 1 means judgement statement is empty */
				if (sym != semic)
				{
					isEmpty = 0;
					expression ();
					pos1 = codeNum; /* save current value of codeNum for backfilling */
					GenINTCode (jpc, 0, 0); /* the position where program jump to hasn't been determined. 
											 * we'll backfill it later */
				}
				else
				{
					pos1 = codeNum;
				}

				GenINTCode (jmp, 0, 0); /* the position where program jump to hasn't been determined. 
										 * we'll backfill it later */

				if (sym == semic)
				{
					ReadSymbol ();
					int L1 = codeNum; /* jumping label */

					if (sym != rparen)
					{
						expression ();
					}
					
					GenINTCode (jmp, L0, 0);

					if (sym == rparen)
					{
						ReadSymbol ();
						int L2 = codeNum; /* jumping label */
						statement ();

						/* backfill 'continue' statement */
						for (int i = startContinueNum; i < ctnNum; i++)
						{
							int pos = continueList[i];
							code[pos].opr1 = codeNum;
						}
						ctnNum = startContinueNum; /* set the value of ctnNum to the value
													* that is before analyzing ForStat */
						
						GenINTCode (jmp, L1, 0);
						
						/* backfill the position where program jump to */
						if (!isEmpty)
						{
							code[pos1].opr1 = codeNum;
							code[pos1 + 1].opr1 = L2;
						}
						else
						{
							code[pos1].opr1 = L2;
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
		ErrorHandler (30);
	}

	/* backfill 'break' statement */
	for (int i = startBreakNum; i < brkNum; i++)
	{
		int pos = breakList[i];
		code[pos].opr1 = codeNum;
	}
	brkNum = startBreakNum; /* set the value of brkNum to the value
							 * that is before analyzing ForStat */
}