#include "../global.h"

/*
 * compoundStat syntactical analyzer
 */
void compoundStat ()
{
	if (sym == lbrace)
	{
		readSymbol ();
		statementList ();

		if (sym == rbrace)
		{
			readSymbol ();
		}
		else /* the lack of '}' */
		{
			error (4);
		}
	}
	else /* the lack of '{' */
	{
		error (5);
	}
}