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
		gen (opr, 0, 1);
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
				gen (opr, 0, 2);
				break;
			case minus:
				gen (opr, 0, 3);
				break;
			default: /* illegal operator */
				error (30);
		}
	}
}