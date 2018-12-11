#include "../global.h"

/*
 * ExpressionStat syntactical analyzer
 */
void ExpressionStat ()
{
	if (sym != semic)
	{
		expression ();
		if (sym == semic)
		{
			ReadSymbol ();
		}
		else /* the lack of ';' */
		{
			ErrorHandler (10);
		}
	}
	else
	{
		ReadSymbol ();
	}
}