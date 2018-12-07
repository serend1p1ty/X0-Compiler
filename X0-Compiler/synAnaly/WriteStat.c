#include "../global.h"

/*
 * WriteStat syntactical analyzer
 */
void WriteStat ()
{
	if (sym == writesym)
	{
		ReadSymbol ();
		expression ();
		if (sym == semic)
		{
			ReadSymbol ();
		}
		else /* the lack of ';' */
		{
			ErrorHandler (10);
		}
		GenerateINTCode (opr, 15, 0, 0); /* output the top element */
	}
	else /* the lack of 'write' */
	{
		ErrorHandler (22);
	}
}