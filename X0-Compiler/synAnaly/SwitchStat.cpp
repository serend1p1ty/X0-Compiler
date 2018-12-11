#include "../global.h"

/*
 * SwitchStat syntactical analyzer
 */
void SwitchStat ()
{
	int startBreakNum = brkNum; /* save the number of 'break' statement to be backfilled before analyzing SwitchStat */
	
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
							code[pos1].opr1 = codeNum; /* backfill */
						}			
						ReadSymbol ();
						if (sym == intnum)
						{
							GenINTCode (lit, intNum, 0);
							GenINTCode (opr, 21, 0); /* '==' operation */
							GenINTCode (jpc, 0, 0);
							pos1 = codeNum - 1;
							ReadSymbol ();
							if (sym == colonsym)
							{
								ReadSymbol ();
								if (pos2 != -1)
								{
									code[pos2].opr1 = codeNum; /* backfill */
								}
								StatementList ();
								GenINTCode (jmp, 0, 0);
								pos2 = codeNum - 1;
							}
							else /* the lack of ':' */
							{
								ErrorHandler (37);
							}
						}
						else /* the lack of integer */
						{
							ErrorHandler (8);
						}
					}

					if (pos1 != -1)
					{
						code[pos1].opr1 = codeNum; /* backfill */
					}

					if (pos2 != -1)
					{
						code[pos2].opr1 = codeNum; /* backfill */
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
							ErrorHandler (37);
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
		ErrorHandler (36);
	}

	/* backfill 'break' statement */
	for (int i = startBreakNum; i < brkNum; i++)
	{
		int pos = breakList[i];
		code[pos].opr1 = codeNum;
	}
	brkNum = startBreakNum; /* set the value of brkNum to the value
							 * that is before analyzing SwitchStat */
}