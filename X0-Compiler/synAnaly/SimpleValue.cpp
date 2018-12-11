#include "../global.h"

/*
 * SimpleValue syntactical analyzer
 */
void SimpleValue ()
{
	if (sym == oddsym)
	{
		ReadSymbol ();
		AdditiveExpr ();
		GenINTCode (opr, 20, 0); /* ODD operation */
	}
	else
	{
		AdditiveExpr ();

		if (sym == great || sym == less || sym == greateql
			|| sym == lesseql || sym == eqleql || sym == neql)
		{
			enum symbol tempSym = sym; /* save current value of sym */
			ReadSymbol ();
			AdditiveExpr ();

			/* >, <, >=, <=, ==, != */
			switch (tempSym)
			{
				case great:
					GenINTCode (opr, 12, 0);
					break;
				case less:
					GenINTCode (opr, 10, 0);
					break;
				case greateql:
					GenINTCode (opr, 11, 0);
					break;
				case lesseql:
					GenINTCode (opr, 13, 0);
					break;
				case eqleql:
					GenINTCode (opr, 8, 0);
					break;
				case neql:
					GenINTCode (opr, 9, 0);
					break;
				default: /* illegal operator */
					ErrorHandler (30);
			}
		}
	}
}