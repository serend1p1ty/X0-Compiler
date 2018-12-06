#include "../global.h"

/*
 * simple_value syntactical analyzer
 */
void simple_value ()
{
	if (sym == oddsym)
	{
		readSymbol ();
		additive_expr ();
		gen (opr, 20, 0, 0); /* ODD operation */
	}
	else
	{
		additive_expr ();

		if (sym == great || sym == less || sym == greateql
			|| sym == lesseql || sym == eqleql || sym == neql)
		{
			enum symbol tempSym = sym; /* save current value of sym */
			readSymbol ();
			additive_expr ();

			/* >, <, >=, <=, ==, != */
			switch (tempSym)
			{
				case great:
					gen (opr, 12, 0, 0);
					break;
				case less:
					gen (opr, 10, 0, 0);
					break;
				case greateql:
					gen (opr, 11, 0, 0);
					break;
				case lesseql:
					gen (opr, 13, 0, 0);
					break;
				case eqleql:
					gen (opr, 8, 0, 0);
					break;
				case neql:
					gen (opr, 9, 0, 0);
					break;
				default: /* illegal operator */
					error (30);
			}
		}
	}
}