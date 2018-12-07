#include "../global.h"

/*
 * DoWhileStat syntactical analyzer
 */
void DoWhileStat ()
{
	int startBreakNum = iterBreakList; /* save the number of break statement to be backfilled before analyzing DoWhileStat */
	int startContinueNum = iterCtnList; /* save the number of continue statement to be backfilled before analyzing DoWhileStat */

	if (sym == dosym)
	{
		ReadSymbol ();
		if (sym == lbrace)
		{
			ReadSymbol ();
			int pos = iterCode; /* save the position of fist code of StatementList */ 
			StatementList ();

			/* backfill continue statement */
			for (int i = startContinueNum; i < iterCtnList; i++)
			{
				int pos = continueList[i];
				code[pos].operand1 = iterCode;
			}
			iterCtnList = startContinueNum; /* set the value of iterCtnList to the value
											 * that is before analysing DoWhileStat */

			if (sym == rbrace)
			{
				ReadSymbol ();
				if (sym == whilesym)
				{
					ReadSymbol ();
					if (sym == lparen)
					{
						ReadSymbol ();
						expression ();
						GenerateINTCode (jpc, iterCode + 2, 0, 0);
						GenerateINTCode (jmp, pos, 0, 0);
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
						else /* the lack of '}' */
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
								    * that is before analysing DoWhileStat */
}