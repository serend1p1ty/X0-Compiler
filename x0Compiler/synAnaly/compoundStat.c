#include "../global.h"

/*
 * compoundStat syntactical analyzer
 */
void compoundStat ()
{
	if (sym == lbrace)
	{
		getSym ();
		statementList ();

		if (sym == rbrace)
		{
			getSym ();
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