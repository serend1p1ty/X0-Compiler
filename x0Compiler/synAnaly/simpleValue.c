#include "../global.h"

/*
 * simpleValue syntactical analyzer
 */
void simpleValue ()
{
	if (sym == oddsym)
	{
		getSym ();
		additiveExpr ();
		gen (opr, 20, 0, 0); /* ODD operation */
	}
	else
	{
		additiveExpr ();

		if (sym == great || sym == less || sym == greateql
			|| sym == lesseql || sym == eqleql || sym == neql)
		{
			enum symbol tempSym = sym; /* save current value of sym */
			getSym ();
			additiveExpr ();

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