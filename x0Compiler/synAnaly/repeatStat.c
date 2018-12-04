#include "../global.h"

/*
 * repeatStat syntactical analyzer
 */
void repeatStat ()
{
	if (sym == reptsym)
	{
		getSym ();

		if (sym == lbrace)
		{
			getSym ();
			int pos = iterCode; /* save the position of statementList's first code */
			statementList ();

			if (sym == rbrace)
			{
				getSym ();

				if (sym == untlsym)
				{
					getSym ();

					if (sym == lparen)
					{
						getSym ();
						expression ();
						gen (jpc, pos, 0, 0);

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