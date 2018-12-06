#include "../global.h"

/*
 * factor syntactical analyzer
 */
void factor ()
{
	int flag = 0; /* flag = 1 means logical inversion operator has appeared */

	if (sym == notsym)
	{
		flag = 1;
		readSymbol ();
	}

	if (sym == lparen)
	{
		readSymbol ();
		expression ();

		if (sym == rparen)
		{
			readSymbol ();
		}
		else /* the lack of ')' */
		{
			error (14);
		}
	}
	else if (sym == ident || sym == incsym || sym == decsym) /* sym belong to first(variable) */
	{
		enum objectKind kind;
		int offset;
		int IncOrDec;	/* 1: Increase after variable   2: decrease after variable
					     * 3: Increase before variable  4: decrease before variable
					     * 5: without Increase or decrease */
		variable (&kind, &offset, &IncOrDec);

		switch (IncOrDec)
		{
			case 1:
				gen (add, offset, 1, 0);
				gen (lod, offset, 0, 0);
				gen (tad, -1, 0, 0);
				break;
			case 2:
				gen (add, offset, -1, 0);
				gen (lod, offset, 0, 0);
				gen (tad, 1, 0, 0);
				break;
			case 3:
				gen (add, offset, 1, 0);
				gen (lod, offset, 0, 0);
				break;
			case 4:
				gen (add, offset, -1, 0);
				gen (lod, offset, 0, 0);
				break;
			case 5:
				gen (lod, offset, 0, 0);
				break;
		}
	}
	else if (sym == intnum)
	{
		gen (lit, 1, intNum, 0);
		readSymbol ();
	}
	else if (sym == doublenum)
	{
		gen (lit, 2, 0, doubleNum);
		readSymbol ();
	}
	else if (sym == truesym || sym == falsesym)
	{
		gen (lit, 1, sym == truesym, 0); /* the value of 'true' is 1, value of 'false' is 0 */
		readSymbol ();
	}
	else /* sym isn't belong to first(factor) */
	{
		error (15);
	}

	/* logic inversion operator has appeared */
	if (flag)
	{
		gen (opr, 18, 0, 0);
	}
}