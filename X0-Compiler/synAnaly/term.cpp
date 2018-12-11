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
				GenINTCode (opr, 4, 0);
				break;
			case slash:
				GenINTCode (opr, 5, 0);
				break;
			case modsym:
				GenINTCode (opr, 6, 0);
				break;
		}
	}
}