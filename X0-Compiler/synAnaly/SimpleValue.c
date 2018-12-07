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
		GenerateINTCode (opr, 20, 0, 0); /* ODD operation */
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
					GenerateINTCode (opr, 12, 0, 0);
					break;
				case less:
					GenerateINTCode (opr, 10, 0, 0);
					break;
				case greateql:
					GenerateINTCode (opr, 11, 0, 0);
					break;
				case lesseql:
					GenerateINTCode (opr, 13, 0, 0);
					break;
				case eqleql:
					GenerateINTCode (opr, 8, 0, 0);
					break;
				case neql:
					GenerateINTCode (opr, 9, 0, 0);
					break;
				default: /* illegal operator */
					ErrorHandler (30);
			}
		}
	}
}