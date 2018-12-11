#include "../global.h"

/*
 * AdditiveExpr syntactical analyzer
 */
void AdditiveExpr ()
{
	if (sym == minus) /* here see '-' as negtive sign */
	{
		ReadSymbol ();
		term ();
		GenINTCode (opr, 1, 0);
	}
	else
	{
		term ();
	}

	while (sym == plus || sym == minus)
	{
		Symbol tempSym = sym; /* save current symbol */
		ReadSymbol ();
		term ();

		switch (tempSym)
		{
			case plus:
				GenINTCode (opr, 2, 0);
				break;
			case minus:
				GenINTCode (opr, 3, 0);
				break;
		}
	}
}