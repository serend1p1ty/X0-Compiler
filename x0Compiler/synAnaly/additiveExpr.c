#include "../global.h"

/*
 * additiveExpr syntactical analyzer
 */
void additiveExpr ()
{
	if (sym == minus) /* here see '-' as negtive sign */
	{
		getSym ();
		term ();
		gen (opr, 1, 0, 0);
	}
	else
	{
		term ();
	}

	while (sym == plus || sym == minus)
	{
		enum symbol tempSym = sym; /* save current symbol */
		getSym ();
		term ();

		switch (tempSym)
		{
			case plus:
				gen (opr, 2, 0, 0);
				break;
			case minus:
				gen (opr, 3, 0, 0);
				break;
			default: /* illegal operator */
				error (30);
		}
	}
}