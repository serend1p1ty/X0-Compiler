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
				gen (opr, 0, 4);
				break;
			case slash:
				gen (opr, 0, 5);
				break;
			case modsym:
				gen (opr, 0, 6);
				break;
			default: /* illegal operator */
				error (30);
		}
	}
}