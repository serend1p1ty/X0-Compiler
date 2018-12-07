#include "../global.h"

/*
 * ContinueStat syntactical analyzer
 */
void ContinueStat ()
{
	if (sym == ctnsym)
	{
		ReadSymbol ();
		if (sym == semic)
		{
			ReadSymbol ();
			GenerateINTCode (jmp, 0, 0, 0);

			/* save the position of 'continue' statement for backfilling later */
			continueList[iterCtnList++] = iterCode - 1;
		}
		else /* the lack of ';' */
		{
			ErrorHandler (10);
		}
	}
	else /* the lack of 'continue' */
	{
		ErrorHandler (36);
	}
}