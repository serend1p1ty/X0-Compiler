#include "../global.h"

/*
 * CompoundStat syntactical analyzer
 */
void CompoundStat ()
{
	if (sym == lbrace)
	{
		ReadSymbol ();
		StatementList ();
		if (sym == rbrace)
		{
			ReadSymbol ();
		}
		else /* the lack of '}' */
		{
			ErrorHandler (4);
		}
	}
	else /* the lack of '{' */
	{
		ErrorHandler (5);
	}
}