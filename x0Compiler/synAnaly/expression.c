#include "../global.h"

/*
 * expression syntactical analyzer
 */
void expression ()
{
	if (sym == ident) /* need to read more symbols to determine whether current statement is assignment statement */
	{
		backup (); /* backup the status of lexical analysing */

		int size1;
		int size2;
		int offset;
		enum objectKind kind;
		simpleVariable (&kind, &offset, &size1, &size2);

		if (sym == eql) /* current statement is assignment statement */
		{
			getSym ();
			expression ();

			if (kind == intArray || kind == charArray 
				|| kind == boolArray || kind == doubleArray)
			{
				/* store the value of top element in a 1-dimension array element */
				if (size2 == 1)
				{
					gen (sto2, offset, 0, 0);
				}
				else /* store the value of top element in a 2-dimension array element */
				{
					gen (sto3, offset, size2, 0);
				}
			}
			else /* store the value of top element in a variable */
			{
				gen (sto, offset, 0, 0);
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