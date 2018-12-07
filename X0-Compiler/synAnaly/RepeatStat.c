#include "../global.h"

/*
 * RepeatStat syntactical analyzer
 */
void RepeatStat ()
{
	int startBreakNum = iterBreakList; /* save the number of break statement to be backfilled before analysing RepeatStat */
	int startContinueNum = iterCtnList; /* save the number of continue statement to be backfilled before analysing RepeatStat */

	if (sym == reptsym)
	{
		ReadSymbol ();
		if (sym == lbrace)
		{
			ReadSymbol ();
			int pos = iterCode; /* save the position of StatementList's first code */
			StatementList ();

			/* backfill continue statement */
			for (int i = startContinueNum; i < iterCtnList; i++)
			{
				int pos = continueList[i];
				code[pos].operand1 = iterCode;
			}
			iterCtnList = startContinueNum; /* set the value of iterCtnList to the value
											 * that is before analysing RepeatStat */

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
						GenerateINTCode (jpc, pos, 0, 0);
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
					ErrorHandler (21);
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
		ErrorHandler (39);
	}

	/* backfill break statement */
	for (int i = startBreakNum; i < iterBreakList; i++)
	{
		int pos = breakList[i];
		code[pos].operand1 = iterCode;
	}
	iterBreakList = startBreakNum; /* set the value of iterBreakList to the value
								    * that is before analysing RepeatStat */
}