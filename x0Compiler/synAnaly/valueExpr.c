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
		getSym ();
		simpleValue ();

		switch (tempSym)
		{
			case andsym:
				gen (opr, 0, 16);
				break;
			case orsym:
				gen (opr, 0, 17);
				break;
			case xorsym:
				gen (opr, 0, 19);
				break;
			default: /* illegal operator */
				error (30);
		}
	}
}