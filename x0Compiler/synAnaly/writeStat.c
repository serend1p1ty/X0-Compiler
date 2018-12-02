#include "../global.h"

/*
 * writeStat syntactical analyzer
 */
void writeStat ()
{
	if (sym == writesym)
	{
		getSym ();
		expression ();

		if (sym == semic)
		{
			getSym ();
		}
		else /* the lack of ';' */
		{
			error (10);
		}

		gen (opr, 0, 15); /* output the top element */
	}
	else /* the lack of 'write' */
	{
		error (22);
	}
}