#include "../global.h"

/*
 * BreakStat syntactical analyzer
 */
void BreakStat ()
{
	if (sym == brksym)
	{
		ReadSymbol ();
		if (sym == semic)
		{
			ReadSymbol ();
			GenINTCode (jmp, 0, 0);
			breakList[brkNum++] = codeNum - 1;
		}
		else /* the lack of ';' */
		{
			ErrorHandler (10);
		}
	}
	else /* the lack of 'break' */
	{
		ErrorHandler (33);
	}
}