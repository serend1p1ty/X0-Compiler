#include "../global.h"

/*
 * ReturnStat syntactical analyzer
 */
void ReturnStat ()
{
	if (sym == retsym)
	{
		ReadSymbol ();

		if (sym != semic)
		{
			ValueExpr ();
		}

		if (sym == semic)
		{
			ReadSymbol ();
			GenINTCode (opr, 0, fctNum - 1);
		}
		else /* the lack of ';' */
		{
			ErrorHandler (10);
		}
	}
}