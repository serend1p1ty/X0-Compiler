#include "../global.h"

/*
 * exitStat syntactical analyzer
 */
void exitStat ()
{
	if (sym == exitsym)
	{
		getSym ();

		if (sym == lparen)
		{
			getSym ();

			if (sym == intnum)
			{
				getSym ();
				gen (lit, 1, intNum, 0);

				if (sym == rparen)
				{
					getSym ();

					if (sym == semic)
					{
						getSym ();
						gen (opr, 7, 0, 0); /* execute 'exit' function */
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
			else /* the lack of INT number */
			{
				error (8);
			}
		}
		else /* the lack of '(' */
		{
			error (16);
		}
	}
	else /* the lack of 'exit' */
	{
		error (35);
	}
}