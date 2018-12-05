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
		getSym ();
	}

	if (sym == lparen)
	{
		getSym ();
		expression ();

		if (sym == rparen)
		{
			getSym ();
		}
		else /* the lack of ')' */
		{
			error (14);
		}
	}
	else if (sym == ident || sym == incsym || sym == decsym) /* sym belong to first(variable) */
	{
		int size1;
		int size2;
		int offset;
		enum objectKind kind;
		int IncOrDec;	/* 1: Increase after variable   2: decrease after variable
					     * 3: Increase before variable  4: decrease before variable
					     * 5: without Increase or decrease */
		variable (&kind, &offset, &size1, &size2, &IncOrDec);

		if (kind == intArray || kind == charArray
			|| kind == boolArray || kind == doubleArray)
		{
			if (size2 == 1) /* load a 1-dimension array element */
			{
				switch (IncOrDec)
				{
					case 1:
						gen (add2, offset, 1, 0);
						gen (lod2, offset, 0, 0);
						gen (tad, -1, 0, 0);
						break;
					case 2:
						gen (add2, offset, -1, 0);
						gen (lod2, offset, 0, 0);
						gen (tad, 1, 0, 0);
						break;
					case 3:
						gen (add2, offset, 1, 0);
						gen (lod2, offset, 0, 0);
						break;
					case 4:
						gen (add2, offset, -1, 0);
						gen (lod2, offset, 0, 0);
						break;
					case 5:
						gen (lod2, offset, 0, 0);
						break;
				}
			}
			else /* load a 2-dimension array element */
			{
				switch (IncOrDec)
				{
					case 1:
						gen (add3, offset, size2, 1);
						gen (lod3, offset, size2, 0);
						gen (tad, -1, 0, 0);
						break;
					case 2:
						gen (add3, offset, size2, -1);
						gen (lod3, offset, size2, 0);
						gen (tad, 1, 0, 0);
						break;
					case 3:
						gen (add3, offset, size2, 1);
						gen (lod3, offset, size2, 0);
						break;
					case 4:
						gen (add3, offset, size2, -1);
						gen (lod3, offset, size2, 0);
						break;
					case 5:
						gen (lod3, offset, size2, 0);
						break;
				}
			}
		}
		else /* load a variable */
		{
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
	}
	else if (sym == intnum)
	{
		gen (lit, 1, intNum, 0);
		getSym ();
	}
	else if (sym == doublenum)
	{
		gen (lit, 2, 0, doubleNum);
		getSym ();
	}
	else if (sym == truesym || sym == falsesym)
	{
		gen (lit, 1, sym == truesym, 0); /* the value of 'true' is 1, value of 'false' is 0 */
		getSym ();
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