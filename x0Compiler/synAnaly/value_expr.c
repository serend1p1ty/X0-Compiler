#include "../global.h"

/*
 * value_expr syntactical analyzer
 */
void value_expr ()
{
	simple_value ();

	while (sym == andsym || sym == orsym || sym == xorsym)
	{
		enum symbol tempSym = sym; /* save current value of sym */
		readSymbol ();
		simple_value ();

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