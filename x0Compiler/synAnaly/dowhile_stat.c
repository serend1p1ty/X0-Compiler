#include "../global.h"

/*
 * dowhileStat syntactical analyzer
 */
void dowhileStat ()
{
	int startBreakNum = iterBreakList; /* save the number of break statement to be backfilled before analysing dowhileStat */
	int startContinueNum = iterCtnList; /* save the number of continue statement to be backfilled before analysing dowhileStat */

	if (sym == dosym)
	{
		readSymbol ();

		if (sym == lbrace)
		{
			readSymbol ();
			int pos = iterCode; /* save the position of fist code of statementList */ 
			statementList ();

			/* backfill continue statement */
			for (int i = startContinueNum; i < iterCtnList; i++)
			{
				int pos = continueList[i];
				code[pos].operand1 = iterCode;
			}
			iterCtnList = startContinueNum; /* set the value of iterCtnList to the value
											 * that is before analysing dowhileStat */

			if (sym == rbrace)
			{
				readSymbol ();

				if (sym == whilesym)
				{
					readSymbol ();

					if (sym == lparen)
					{
						readSymbol ();
						expression ();
						gen (jpc, iterCode + 2, 0, 0);
						gen (jmp, pos, 0, 0);

						if (sym == rparen)
						{
							readSymbol ();

							if (sym == semic)
							{
								readSymbol ();
							}
							else /* the lack of ';' */
							{
								error (10);
							}
						}
						else /* the lack of '}' */
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
			}
			else /* the lack of '}' */
			{
				error (4);
			}
		}
		else /* the lack of '{' */
		{
			error (5);
		}
	}
	else /* the lack of 'do' */
	{
		error (39);
	}

	/* backfill break statement */
	for (int i = startBreakNum; i < iterBreakList; i++)
	{
		int pos = breakList[i];
		code[pos].operand1 = iterCode;
	}
	iterBreakList = startBreakNum; /* set the value of iterBreakList to the value
								    * that is before analysing dowhileStat */
}