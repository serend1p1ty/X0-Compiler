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
				GenerateINTCode (opr, 16, 0, 0);
				break;
			case orsym:
				GenerateINTCode (opr, 17, 0, 0);
				break;
			case xorsym:
				GenerateINTCode (opr, 19, 0, 0);
				break;
			default: /* illegal operator */
				ErrorHandler (30);
		}
	}
}