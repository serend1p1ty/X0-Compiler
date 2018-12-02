#include "../global.h"

/*
 * expression syntactical analyzer
 */
void expression ()
{
	if (sym == hashsym)	/* sym == '#' */	
	{
		getSym ();

		int offset;    /* the offset relative to the base address of current activity record */
		int isArray;   /* 1: 'variable' is array element   0: 'variable' is just a variable */
		int IncOrDec;  /* 1: auto-adding after variable   2: auto-decreasing after variable 
					    * 3: auto-adding before variable  4: auto-decreasing before variable 
					    * 5: without auto-adding or auto-decreasing */
		int identType; /* 1: INT   2: DOUBLE   3: CHAR   4: BOOL */
		variable (&offset, &isArray, &IncOrDec, &identType);

		/* auto-adding or auto-decreasing variable can't be left of assignment statement */
		if (IncOrDec != 5)
		{
			error (32);
		}

		if (sym == eql)
		{
			getSym ();
			expression ();

			/* store the value of top element in variable */
			if (isArray)
			{
				gen (stf, 0, offset);
			}
			else
			{
				gen (sto, 0, offset);
			}
		}
		else /* the lack of '=' */
		{
			error (11);
		}
	}
	else if (sym == lparen || sym == intnum || sym == ident || sym == minus
			|| sym == incsym || sym == decsym || sym == oddsym || sym == notsym
			|| sym == truesym || sym == falsesym || sym == doublenum)	/* sym belong to first(valueExpr) */
	{
		valueExpr ();
	}
	else /* sym isn't belong to first(expression) */
	{
		error (12);
	}
}