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
		int offset;     /* the offset relative to the base address of current activity record */
		int isArray;    /* 1: 'variable' is array element   0: 'variable' is just a variable */
		int IncOrDec;   /* 1: auto-adding after variable   2: auto-decreasing after variable
					     * 3: auto-adding before variable  4: auto-decreasing before variable
					     * 5: without auto-adding or auto-decreasing */
		int identType;  /* 1: INT   2: DOUBLE   3: CHAR   4: BOOL */
		variable (&offset, &isArray, &IncOrDec, &identType);

		/* load variable */
		if (isArray)
		{
			switch (IncOrDec)
			{
				case 1:
					gen (adf, 0, offset);
					gen (lof, 0, offset);
					gen (tad, 0, -1);
					break;
				case 2:
					gen (mif, 0, offset);
					gen (lof, 0, offset);
					gen (tad, 0, 1);
					break;
				case 3:
					gen (adf, 0, offset);
					gen (lof, 0, offset);
					break;
				case 4:
					gen (mif, 0, offset);
					gen (lof, 0, offset);
					break;
				case 5:
					gen (lof, 0, offset);
					break;
			}
		}
		else
		{
			switch (IncOrDec)
			{
				case 1:
					gen (add, 0, offset);
					gen (lod, 0, offset);
					gen (tad, 0, -1);
					break;
				case 2:
					gen (mis, 0, offset);
					gen (lod, 0, offset);
					gen (tad, 0, 1);
					break;
				case 3:
					gen (add, 0, offset);
					gen (lod, 0, offset);
					break;
				case 4:
					gen (mis, 0, offset);
					gen (lod, 0, offset);
					break;
				case 5:
					gen (lod, 0, offset);
					break;
			}
		}
	}
	else if (sym == intnum)
	{
		gen (lit, 1, intNum);
		getSym ();
	}
	else if (sym == doublenum)
	{
		gen (lit, 2, doubleNum);
		getSym ();
	}
	else if (sym == truesym || sym == falsesym)
	{
		gen (lit, 4, sym == truesym); /* the value of 'true' is 1, value of 'false' is 0 */
		getSym ();
	}
	else /* sym isn't belong to first(factor) */
	{
		error (15);
	}

	/* logic inversion operator has appeared */
	if (flag)
	{
		gen (opr, 0, 18);
	}
}