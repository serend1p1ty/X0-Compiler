#include "../global.h"

/*
 * ValueExpr syntactical analyzer
 */
void ValueExpr ()
{
	SimpleValue ();
	while (sym == andsym || sym == orsym || sym == xorsym)
	{
		enum symbol tempSym = sym; /* save current value of sym */
		ReadSymbol ();
		SimpleValue ();
		switch (tempSym)
		{
			case andsym:
				GenINTCode (opr, 16, 0);
				break;
			case orsym:
				GenINTCode (opr, 17, 0);
				break;
			case xorsym:
				GenINTCode (opr, 19, 0);
				break;
		}
	}
}