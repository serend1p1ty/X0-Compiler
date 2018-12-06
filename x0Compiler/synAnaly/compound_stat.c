#include "../global.h"

/*
 * compound_stat syntactical analyzer
 */
void compound_stat ()
{
	if (sym == lbrace)
	{
		readSymbol ();
		statement_list ();

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