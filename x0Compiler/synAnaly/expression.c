#include "../global.h"

/*
 * expression syntactical analyzer
 */
void expression ()
{
	if (sym == ident) /* need to read more symbols to determine whether current statement is assignment statement */
	{
		backup (); /* backup the status of lexical analysing */

		int offset;    /* the offset relative to the base address of current activity record */
		int isArray;   /* 1: 'variable' is array element   0: 'variable' is just a variable */
		int identType; /* 1: INT   2: DOUBLE   3: CHAR   4: BOOL */
		simpleVariable (&offset, &isArray, &identType);

		if (sym == eql) /* current statement is assignment statement */
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
		else /* current statement is valueExpr */
		{
			recover (); /* recover the status of lexical analysing from backups */
			valueExpr ();
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