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
		GenerateINTCode (opr, 1, 0, 0);
	}
	else
	{
		term ();
	}

	while (sym == plus || sym == minus)
	{
		enum symbol tempSym = sym; /* save current symbol */
		ReadSymbol ();
		term ();

		switch (tempSym)
		{
			case plus:
				GenerateINTCode (opr, 2, 0, 0);
				break;
			case minus:
				GenerateINTCode (opr, 3, 0, 0);
				break;
			default: /* illegal operator */
				ErrorHandler (30);
		}
	}
}