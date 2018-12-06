#include "../global.h"

/*
 * type syntactical analyzer
 */
void type ()
{
	/* sym isn't belong to first(type) */
	if (sym != charsym && sym != intsym && sym != bolsym && sym != dblsym)
	{
		error (20);
	}

	readSymbol ();
}