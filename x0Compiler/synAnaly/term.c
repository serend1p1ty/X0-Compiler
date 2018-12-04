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
		getSym ();
		factor ();

		switch (tempSym)
		{
			case times:
				gen (opr, 4, 0, 0);
				break;
			case slash:
				gen (opr, 5, 0, 0);
				break;
			case modsym:
				gen (opr, 6, 0, 0);
				break;
			default: /* illegal operator */
				error (30);
		}
	}
}