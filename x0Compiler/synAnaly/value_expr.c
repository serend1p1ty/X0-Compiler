#include "../global.h"

/*
 * valueExpr syntactical analyzer
 */
void valueExpr ()
{
	simpleValue ();

	while (sym == andsym || sym == orsym || sym == xorsym)
	{
		enum symbol tempSym = sym; /* save current value of sym */
		readSymbol ();
		simpleValue ();

		switch (tempSym)
		{
			case andsym:
				gen (opr, 16, 0, 0);
				break;
			case orsym:
				gen (opr, 17, 0, 0);
				break;
			case xorsym:
				gen (opr, 19, 0, 0);
				break;
			default: /* illegal operator */
				error (30);
		}
	}
}