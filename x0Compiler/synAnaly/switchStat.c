#include "../global.h"

/*
 * switchStat syntactical analyzer
 */
void switchStat ()
{
	int startBreakNum = iterBreakList; /* save the number of break statement to be backfilled before analysing switchStat */
	
	if (sym == swtcsym)
	{
		getSym ();

		if (sym == lparen)
		{
			getSym ();
			expression ();

			if (sym == rparen)
			{
				getSym ();

				if (sym == lbrace)
				{
					getSym ();
					int pos1 = -1; /* the position of 'jpc' in previous 'case' statement */
					int pos2 = -1; /* the position of 'jmp' in previous 'case' statement */

					while (sym == cassym)
					{
						if (pos1 != -1)
						{
							code[pos1].operand1 = iterCode; /* backfill */
						}
						
						getSym ();

						if (sym == intnum)
						{
							gen (lit, 1, intNum, 0);
							gen (opr, 21, 0, 0); /* '==' operation */
							gen (jpc, 0, 0, 0);
							pos1 = iterCode - 1;
							getSym ();

							if (sym == colonsym)
							{
								getSym ();

								if (pos2 != -1)
								{
									code[pos2].operand1 = iterCode; /* backfill */
								}

								statementList ();
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
						getSym ();

						if (sym == colonsym)
						{
							getSym ();
							statementList ();
						}
						else /* the lack of ':' */
						{
							error (38);
						}
					}

					if (sym == rbrace)
					{
						getSym ();
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
									* that is before analysing switchStat */
}