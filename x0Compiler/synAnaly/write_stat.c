#include "../global.h"

/*
 * write_stat syntactical analyzer
 */
void write_stat ()
{
	if (sym == writesym)
	{
		readSymbol ();
		expression ();

		if (sym == semic)
		{
			readSymbol ();
		}
		else /* the lack of ';' */
		{
			error (10);
		}

		gen (opr, 15, 0, 0); /* output the top element */
	}
	else /* the lack of 'write' */
	{
		error (22);
	}
}