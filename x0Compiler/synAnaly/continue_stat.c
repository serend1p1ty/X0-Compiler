#include "../global.h"

/*
 * continue_stat syntactical analyzer
 */
void continue_stat ()
{
	if (sym == ctnsym)
	{
		readSymbol ();

		if (sym == semic)
		{
			readSymbol ();
			gen (jmp, 0, 0, 0);
			continueList[iterCtnList++] = iterCode - 1;
		}
		else /* the lack of ';' */
		{
			error (10);
		}
	}
	else /* the lack of 'continue' */
	{
		error (36);
	}
}