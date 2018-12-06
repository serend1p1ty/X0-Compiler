#include "../global.h"

/*
 * switch_stat syntactical analyzer
 */
void switch_stat ()
{
	int startBreakNum = iterBreakList; /* save the number of break statement to be backfilled before analysing switch_stat */
	
	if (sym == swtcsym)
	{
		readSymbol ();

		if (sym == lparen)
		{
			readSymbol ();
			expression ();

			if (sym == rparen)
			{
				readSymbol ();

				if (sym == lbrace)
				{
					readSymbol ();
					int pos1 = -1; /* the position of 'jpc' in previous 'case' statement */
					int pos2 = -1; /* the position of 'jmp' in previous 'case' statement */

					while (sym == cassym)
					{
						if (pos1 != -1)
						{
							code[pos1].operand1 = iterCode; /* backfill */
						}
						
						readSymbol ();

						if (sym == intnum)
						{
							gen (lit, 1, intNum, 0);
							gen (opr, 21, 0, 0); /* '==' operation */
							gen (jpc, 0, 0, 0);
							pos1 = iterCode - 1;
							readSymbol ();

							if (sym == colonsym)
							{
								readSymbol ();

								if (pos2 != -1)
								{
									code[pos2].operand1 = iterCode; /* backfill */
								}

								statement_list ();
								gen (jmp, 0, 0, 0);
								pos2 = iterCode - 1;
							}
							else /* the lack of ':' */
							{
								error (38);
							}
						}
						else /* the lack of INT number */
						{
							error (8);
						}
					}

					if (pos1 != -1)
					{
						code[pos1].operand1 = iterCode; /* backfill */
					}

					if (pos2 != -1)
					{
						code[pos2].operand1 = iterCode; /* backfill */
					}

					if (sym == defausym)
					{
						readSymbol ();

						if (sym == colonsym)
						{
							readSymbol ();
							statement_list ();
						}
						else /* the lack of ':' */
						{
							error (38);
						}
					}

					if (sym == rbrace)
					{
						readSymbol ();
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
	else /* the lack of 'switch' */
	{
		error (37);
	}

	/* backfill break statement */
	for (int i = startBreakNum; i < iterBreakList; i++)
	{
		int pos = breakList[i];
		code[pos].operand1 = iterCode;
	}
	iterBreakList = startBreakNum; /* set the value of iterBreakList to the value
									* that is before analysing switch_stat */
}