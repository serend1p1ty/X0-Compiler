#include "../global.h"

/*
 * breakStat syntactical analyzer
 */
void breakStat ()
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