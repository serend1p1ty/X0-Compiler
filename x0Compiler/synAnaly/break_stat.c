#include "../global.h"

/*
 * break_stat syntactical analyzer
 */
void break_stat ()
{
	if (sym == brksym)
	{
		readSymbol ();

		if (sym == semic)
		{
			readSymbol ();
			gen (jmp, 0, 0, 0);
			breakList[iterBreakList++] = iterCode - 1;
		}
		else /* the lack of ';' */
		{
			error (10);
		}
	}
	else /* the lack of 'break' */
	{
		error (34);
	}
}