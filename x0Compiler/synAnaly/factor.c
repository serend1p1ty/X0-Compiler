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
		int size;       /* 'size' is the space distributed to 'variable' */
		int offset;     /* the offset relative to the base address of current activity record */
		int isArray;    /* 1: 'variable' is array element   0: 'variable' is just a variable */
		int IncOrDec;   /* 1: auto-adding after variable   2: auto-decreasing after variable
					     * 3: auto-adding before variable  4: auto-decreasing before variable
					     * 5: without auto-adding or auto-decreasing */
		int identType;  /* 1: INT   2: DOUBLE   3: CHAR   4: BOOL */
		variable (&offset, &isArray, &IncOrDec, &identType, &size);

		/* load variable */
		if (isArray)
		{
			switch (IncOrDec)
			{
				case 1:
					gen (add2, offset, size, 1);
					gen (lod2, offset, size, 0);
					gen (tad, -1, 0, 0);
					break;
				case 2:
					gen (add2, offset, size, -1);
					gen (lod2, offset, size, 0);
					gen (tad, 1, 0, 0);
					break;
				case 3:
					gen (add2, offset, size, 1);
					gen (lod2, offset, size, 0);
					break;
				case 4:
					gen (add2, offset, size, -1);
					gen (lod2, offset, size, 0);
					break;
				case 5:
					gen (lod2, offset, size, 0);
					break;
			}
		}
		else
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