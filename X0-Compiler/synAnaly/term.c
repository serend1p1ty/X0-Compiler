#include "../global.h"

/*
 * term syntactical analyzer
 */
void term ()
{
	factor ();
	while (sym == times || sym == slash || sym == modsym)
	{
		enum symbol tempSym = sym; /* save current value of sym */
		ReadSymbol ();
		factor ();
		switch (tempSym)
		{
			case times:
				GenerateINTCode (opr, 4, 0, 0);
				break;
			case slash:
				GenerateINTCode (opr, 5, 0, 0);
				break;
			case modsym:
				GenerateINTCode (opr, 6, 0, 0);
				break;
			default: /* illegal operator */
				ErrorHandler (30);
		}
	}
}