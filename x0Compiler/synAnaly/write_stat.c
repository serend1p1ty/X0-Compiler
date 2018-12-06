#include "../global.h"

/*
 * writeStat syntactical analyzer
 */
void writeStat ()
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