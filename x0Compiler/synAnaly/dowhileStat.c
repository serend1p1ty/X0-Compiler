#include "../global.h"

/*
 * dowhileStat syntactical analyzer
 */
void dowhileStat ()
{
	if (sym == dosym)
	{
		getSym ();

		if (sym == lbrace)
		{
			getSym ();
			int pos = iterCode; /* save the position of fist code of statementList */ 
			statementList ();

			if (sym == rbrace)
			{
				getSym ();

				if (sym == whilesym)
				{
					getSym ();

					if (sym == lparen)
					{
						getSym ();
						expression ();
						gen (jpc, 0, iterCode + 2);
						gen (jmp, 0, pos);

						if (sym == rparen)
						{
							getSym ();

							if (sym == semic)
							{
								getSym ();
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
}