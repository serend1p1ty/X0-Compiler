#include "../global.h"

/*
 * breakStat syntactical analyzer
 */
void breakStat ()
{
	if (sym == brksym)
	{
		getSym ();

		if (sym == semic)
		{
			getSym ();
			gen (jmp, 0, 0);
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