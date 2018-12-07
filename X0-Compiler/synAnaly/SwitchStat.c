#include "../global.h"

/*
 * SwitchStat syntactical analyzer
 */
void SwitchStat ()
{
	int startBreakNum = iterBreakList; /* save the number of break statement to be backfilled before analysing SwitchStat */
	
	if (sym == swtcsym)
	{
		ReadSymbol ();
		if (sym == lparen)
		{
			ReadSymbol ();
			expression ();
			if (sym == rparen)
			{
				ReadSymbol ();
				if (sym == lbrace)
				{
					ReadSymbol ();
					int pos1 = -1; /* the position of jpc in previous 'case' statement */
					int pos2 = -1; /* the position of jmp in previous 'case' statement */
					while (sym == cassym)
					{
						if (pos1 != -1)
						{
							code[pos1].operand1 = iterCode; /* backfill */
						}			
						ReadSymbol ();
						if (sym == intnum)
						{
							GenerateINTCode (lit, 1, intNum, 0);
							GenerateINTCode (opr, 21, 0, 0); /* '==' operation */
							GenerateINTCode (jpc, 0, 0, 0);
							pos1 = iterCode - 1;
							ReadSymbol ();
							if (sym == colonsym)
							{
								ReadSymbol ();
								if (pos2 != -1)
								{
									code[pos2].operand1 = iterCode; /* backfill */
								}
								StatementList ();
								GenerateINTCode (jmp, 0, 0, 0);
								pos2 = iterCode - 1;
							}
							else /* the lack of ':' */
							{
								ErrorHandler (38);
							}
						}
						else /* the lack of INT number */
						{
							ErrorHandler (8);
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
						ReadSymbol ();
						if (sym == colonsym)
						{
							ReadSymbol ();
							StatementList ();
						}
						else /* the lack of ':' */
						{
							ErrorHandler (38);
						}
					}

					if (sym == rbrace)
					{
						ReadSymbol ();
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
	else /* the lack of 'switch' */
	{
		ErrorHandler (37);
	}

	/* backfill break statement */
	for (int i = startBreakNum; i < iterBreakList; i++)
	{
		int pos = breakList[i];
		code[pos].operand1 = iterCode;
	}
	iterBreakList = startBreakNum; /* set the value of iterBreakList to the value
									* that is before analysing SwitchStat */
}