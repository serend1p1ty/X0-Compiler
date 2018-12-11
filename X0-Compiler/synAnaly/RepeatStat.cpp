#include "../global.h"

/*
 * RepeatStat syntactical analyzer
 */
void RepeatStat ()
{
	int startBreakNum = brkNum; /* save the number of 'break' statement to be backfilled before analyzing RepeatStat */
	int startContinueNum = ctnNum; /* save the number of 'continue' statement to be backfilled before analyzing RepeatStat */

	if (sym == reptsym)
	{
		ReadSymbol ();
		if (sym == lbrace)
		{
			ReadSymbol ();
			int pos = codeNum; /* save the position of StatementList's first code */
			StatementList ();

			/* backfill 'continue' statement */
			for (int i = startContinueNum; i < ctnNum; i++)
			{
				int pos = continueList[i];
				code[pos].opr1 = codeNum;
			}
			ctnNum = startContinueNum; /* set the value of ctnNum to the value
										* that is before analyzing RepeatStat */

			if (sym == rbrace)
			{
				ReadSymbol ();
				if (sym == untlsym)
				{
					ReadSymbol ();
					if (sym == lparen)
					{
						ReadSymbol ();
						expression ();
						GenINTCode (jpc, pos, 0);
						if (sym == rparen)
						{
							ReadSymbol ();
							if (sym == semic)
							{
								ReadSymbol ();
							}
							else /* the lack of ';' */
							{
								ErrorHandler (10);
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
				else /* the lack of 'while' */
				{
					ErrorHandler (20);
				}
			}
			else /* the lack of '}' */
			{
				ErrorHandler (4);
			}
		}
		else /* the lack of '{' */
		{
			ErrorHandler (5);
		}
	}
	else /* the lack of 'do' */
	{
		ErrorHandler (38);
	}

	/* backfill 'break' statement */
	for (int i = startBreakNum; i < brkNum; i++)
	{
		int pos = breakList[i];
		code[pos].opr1 = codeNum;
	}
	brkNum = startBreakNum; /* set the value of brkNum to the value
							 * that is before analyzing RepeatStat */
}